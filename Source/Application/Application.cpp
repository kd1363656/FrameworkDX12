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
	if (!m_window.Create(1280 , 720 , L"FrameworkDX12" , L"Window"))
	{
		assert(false && "ウィンドウ作成失敗。");
		return;
	}

	if (!GraphicsDevice::Instance().Init())
	{
		assert(false && "グラフィックスデバイス初期化失敗。");
		return;
	}

	while (true)
	{
		if (!m_window.ProcessMessage())
		{
			break;
		}
	}
}