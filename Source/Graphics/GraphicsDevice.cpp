#include "GraphicsDevice.h"

bool GraphicsDevice::Init(HWND hWnd, int w, int h)
{
	if (!CreateFactory())
	{
		assert(false && "ファクトリー作成失敗");
		return false;
	}

	if (!CreateDevice())
	{
		assert(false && "D3D12デバイス作成失敗");
		return false;
	}

	if (!CreateCommandList())
	{
		assert(false && "コマンドリストの作成失敗");
		return false;
	}

	if (!CreateSwapChain(hWnd , w , h))
	{
		assert(false && "スワップチェインの作成失敗");
		return false;
	}

	return true;
}

bool GraphicsDevice::CreateFactory()
{
	UINT flagsDXGI = 0;
	flagsDXGI |= DXGI_CREATE_FACTORY_DEBUG;
	auto result = CreateDXGIFactory2(flagsDXGI , IID_PPV_ARGS(m_pDxgiFactory.GetAddressOf()));

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool GraphicsDevice::CreateDevice()
{
	ComPtr<IDXGIAdapter>			  pSelectAdapter = nullptr;
	std::vector<ComPtr<IDXGIAdapter>> pAdapters;
	std::vector<DXGI_ADAPTER_DESC>    descs;

	// 使用中PCにあるGPUドライバーを検索して、あれば格納する
	for (UINT index = 0; 1; ++index)
	{
		pAdapters.push_back(nullptr);
		HRESULT ret = m_pDxgiFactory->EnumAdapters(index , &pAdapters[index]);

		if (ret == DXGI_ERROR_NOT_FOUND) { break; }

		descs.push_back({});
		pAdapters[index]->GetDesc(&descs[index]);
	}

	GPUTier gpuTier = GPUTier::Kind;

	// 優先度の高いGPUドライバーを使用する
	for (int i = 0; i < descs.size(); ++i)
	{
		if (std::wstring(descs[i].Description).find(L"NVIDIA") != std::wstring::npos)
		{
			pSelectAdapter = pAdapters[i];
			break;
		}
		else if (std::wstring(descs[i].Description).find(L"Amd") != std::wstring::npos)
		{
			if (gpuTier > GPUTier::Amd)
			{
				pSelectAdapter = pAdapters[i];
				gpuTier        = GPUTier::Amd;
			}
		}
		else if (std::wstring(descs[i].Description).find(L"Intel") != std::wstring::npos)
		{
			if (gpuTier > GPUTier::Inter)
			{
				pSelectAdapter = pAdapters[i];
				gpuTier = GPUTier::Inter;
			}
		}
		else if (std::wstring(descs[i].Description).find(L"Arm") != std::wstring::npos)
		{
			if (gpuTier > GPUTier::Arm)
			{
				pSelectAdapter = pAdapters[i];
				gpuTier        = GPUTier::Arm;
			}
		}
		else if (std::wstring(descs[i].Description).find(L"Qualcomm") != std::wstring::npos)
		{
			if (gpuTier > GPUTier::Qualcom)
			{
				pSelectAdapter = pAdapters[i];
				gpuTier        = GPUTier::Qualcom;
			}
		}
	}

	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1 ,
		D3D_FEATURE_LEVEL_12_0 ,
		D3D_FEATURE_LEVEL_11_1 ,
		D3D_FEATURE_LEVEL_11_0 ,
	};

	D3D_FEATURE_LEVEL featureLevel = {};
	// Direct3Dデバイスの初期化
	for (auto lv : levels)
	{
		if (D3D12CreateDevice(pSelectAdapter.Get() , lv , IID_PPV_ARGS(&m_pDevice)) == S_OK)
		{
			featureLevel = lv;
			break;	//生成可能なバージョンが見つかったらループ打ち切り
		}
	}

	return true;
}

bool GraphicsDevice::CreateCommandList()
{
	auto hr = m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT , IID_PPV_ARGS(&m_pCmdAllocator));

	if (FAILED(hr))
	{
		return false;
	}

	hr = m_pDevice->CreateCommandList(0 , D3D12_COMMAND_LIST_TYPE_DIRECT , m_pCmdAllocator.Get() , 
		nullptr , IID_PPV_ARGS(&m_pCmdList));

	if (FAILED(hr))
	{
		return false;
	}

	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags    = D3D12_COMMAND_QUEUE_FLAG_NONE;			// タイムアウトなし
	cmdQueueDesc.NodeMask = 0;										// アダプターを一つしか使わない時は0でいい
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;	// プライオリティは特に指定なし
	cmdQueueDesc.Type     = D3D12_COMMAND_LIST_TYPE_DIRECT;			// コマンドリストと合わせる

	// キュー作成
	hr = m_pDevice->CreateCommandQueue(&cmdQueueDesc , IID_PPV_ARGS(&m_pCmdQueue));

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool GraphicsDevice::CreateSwapChain(HWND hwnd, int width, int height)
{
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};

	swapchainDesc.Width = width;
	swapchainDesc.Height = height;
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapchainDesc.BufferCount = 2;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	auto result = m_pDxgiFactory->CreateSwapChainForHwnd(m_pCmdQueue.Get() , hwnd , &swapchainDesc , nullptr , nullptr , (IDXGISwapChain1**)m_pSwapChain.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	return true;
}