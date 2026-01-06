#pragma once

class GraphicsDevice
{
public:

	bool Init();

private:

	bool CreateFactory();

	bool CreateDevice();

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

	GraphicsDevice () = default;
	~GraphicsDevice() = default;

public:

	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};