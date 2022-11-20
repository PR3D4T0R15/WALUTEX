#include <Windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR args, _In_ int ncmdshow)
{
	WNDCLASSEX window;
	HWND hwnd;
	MSG messages;

	window.cbSize = sizeof(WNDCLASSEX);
	window.style = 0;
	window.lpfnWndProc = WindowProcedure;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;	
	window.hInstance = hInst;
	window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	window.lpszMenuName = NULL;	
	window.lpszClassName = L"window";
	window.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&window))
	{
		MessageBoxEx(NULL, L"ERROR creating window class", L"MASTER ERROR", MB_ICONERROR, 0);
		return -1;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"window", L"WALUTEX", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, 100, 100, 800, 300, NULL, NULL, hInst, NULL);

	if (hwnd == NULL)
	{
		MessageBoxEx(NULL, L"ERROR creating window", L"MASTER ERROR", MB_ICONERROR, 0);
		return -1;
	}

	ShowWindow(hwnd, ncmdshow);
	UpdateWindow(hwnd);

	while (GetMessageW(&messages, NULL, NULL, NULL))
	{
		TranslateMessage(&messages);
		DispatchMessageW(&messages);
	}

	return 0;
}

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
		break;

	case WM_COMMAND:
		break;

	default:
		return DefWindowProc(hwnd, messages, wparam, lparam);
		break;
	}
}