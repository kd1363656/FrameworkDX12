#pragma once

class RTVHeap;

class GraphicsDevice
{
public:

	bool Init(HWND hWnd , int w , int h);

	void ScreenFlip();

	void WaitForCommandQueue();

	auto& GetDevice() { return m_pDevice; }

	auto& GetCmdList() { return m_pCmdList; }

private:

	bool CreateFactory();

	// デバイスの作成
	bool CreateDevice();

	// コマンドリストの作成
	bool CreateCommandList();

	// スワップチェイン作成
	bool CreateSwapChain(HWND hwnd , int width  , int height);

	// スワップチェイン"RTV"の作成
	bool CreateSwapChainRTV();

	bool CreateFence();

	void SetResourceBarrier(ID3D12Resource* pResource , D3D12_RESOURCE_STATES before , D3D12_RESOURCE_STATES after);

	void EnableDebugLayer();
	
	enum class GPUTier
	{
		NVIDA   ,
		Amd     ,
		Inter   ,
		Arm     ,
		Qualcom ,
		Kind    ,
	};

	ComPtr<ID3D12Device8>   m_pDevice      = nullptr;
	ComPtr<IDXGIFactory6>   m_pDxgiFactory = nullptr;
	ComPtr<IDXGISwapChain4> m_jpSwapChain  = nullptr;

	ComPtr<ID3D12CommandAllocator>     m_pCmdAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList6> m_pCmdList      = nullptr;
	ComPtr<ID3D12CommandQueue>         m_pCmdQueue     = nullptr;

	ComPtr<IDXGISwapChain4> m_pSwapChain = nullptr;

	std::array<ComPtr<ID3D12Resource>, 2> m_pSwapChainBuffers;
	std::unique_ptr<RTVHeap>			  m_pRTVHeap		  = nullptr;

	ComPtr<ID3D12Fence> m_pFence   = nullptr;
	UINT64              m_fenceVal = 0;

	GraphicsDevice ();
	~GraphicsDevice();

public:

	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};