#pragma once

class Window
{
public:
	
	// ウィンドウ作成
	bool Create(int clientWidth , int clientHeight , const std::wstring& titleName , const std::wstring& windowClassName);

	// ウィンドウメッセージ処理
	bool ProcessMessage();

	HWND GetWndHandle() const { return m_hWnd; }

private:

	HWND m_hWnd;		// ウィンドウハンドル
};