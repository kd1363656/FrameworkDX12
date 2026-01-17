#include "Application.h"

int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR , int)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// メモリリークを知らせる

	CoInitializeEx(nullptr , COINIT_MULTITHREADED);	// "COM"初期化

	Application::Instance().Execute();

	CoUninitialize();	// "COM"解放

	return 0;
}

void Application::Execute()
{
	static const float width  = 1280.0F;
	static const float height = 720.0F;

	if (!m_window.Create(width , height , L"FrameworkDX12" , L"Window"))
	{
		assert(false && "ウィンドウ作成失敗。");
		return;
	}

	if (!GraphicsDevice::Instance().Init(m_window.GetWndHandle() , width , height))
	{
		assert(false && "グラフィックスデバイス初期化失敗。");
		return;
	}

	Mesh mesh;
	mesh.Create(&GraphicsDevice::Instance());

	RenderingSetting renderingSetting = {};
	renderingSetting.InputLayouts     = { InputLayout::POSITION };
	renderingSetting.Formats          = { DXGI_FORMAT_R8G8B8A8_UNORM };
	renderingSetting.IsDepth          = false;
	renderingSetting.IsDepthMask      = false;

	Shader shader;
	shader.Create(&GraphicsDevice::Instance(), L"SimpleShader", renderingSetting , {});

	while (true)
	{
		if (!m_window.ProcessMessage())
		{
			break;
		}

		GraphicsDevice::Instance().Prepare();

		shader.Begin(width , height);
		shader.DrawMesh(mesh);

		GraphicsDevice::Instance().ScreenFlip();
	}
}