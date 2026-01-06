#pragma once

class Window
{
public:
	
	// ウィンドウ作成
	bool Create(int clientWidth , int clientHeight , const std::wstring& l_titleName , const std::wstring& windowClassName);

private:

	HWND m_hWnd;		// ウィンドウハンドル
};