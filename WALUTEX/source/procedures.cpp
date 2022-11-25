#include "procedures.h"
#include "window_functions.h"
#include <Windows.h>

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT messages, WPARAM wparam, LPARAM lparam)
{
	switch (messages)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		CreateMainControls(hwnd);
		CreateListData();
		break;

	case WM_COMMAND:
		break;

	default:
		return DefWindowProc(hwnd, messages, wparam, lparam);
		break;
	}
	return 0;
}