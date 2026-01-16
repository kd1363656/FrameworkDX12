#pragma once

class GraphicsDevice
{
public:

	bool Init(HWND hWnd , int w , int h);

private:

	bool CreateFactory();

	// デバイスの作成
	bool CreateDevice();

	// コマンドリストの作成
	bool CreateCommandList();

	// スワップチェイン作成
	bool CreateSwapChain(HWND hwnd , int width  , int height);

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

	GraphicsDevice () = default;
	~GraphicsDevice() = default;

public:

	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};