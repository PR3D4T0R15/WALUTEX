#include "procedures.h"
#include "window_functions.h"
#include "update_data.h"
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
		ChangeFlag();
		break;

	case WM_COMMAND:
		switch (HIWORD(wparam))
		{
		case CBN_SELCHANGE:
			ChangeFlag();
			break;
		default:
			break;
		}
		switch (wparam)
		{
		case hmenu_updateData:
			getDataFromServer();
			UpdateListData();
			break;

		case converterConvertButton:
			CalculateCurrency();
			break;

		case hmenu_aboutButton:
			MessageBoxEx(NULL, L"Designed by Mateusz Mang", L"INFORMACJA", MB_ICONINFORMATION, 0);
			break;

		default:
			break;
		}
		break;

	default:
		return DefWindowProc(hwnd, messages, wparam, lparam);
		break;
	}
	return 0;
}