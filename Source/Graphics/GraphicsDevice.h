#pragma once

class GraphicsDevice
{
public:

	bool Init();

private:

	bool CreateFactory();

	// デバイスの作成
	bool CreateDevice();

	// コマンドリストの作成
	bool CreateCommandList();

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

	GraphicsDevice () = default;
	~GraphicsDevice() = default;

public:

	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};