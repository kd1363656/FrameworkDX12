#include "Window.h"

LRESULT WindowProcedure(HWND hWnd , UINT message , WPARAM wParam , LPARAM lParam)
{
	// メッセージに処理を選択
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);	// OSに対して終了を伝える
		break;
	default:
		return DefWindowProc(hWnd , message , wParam , lParam);
		break;
	}

	return 0;
}