#include <Windows.h>
#include "resource.h"
#include "update_data.h"
#include "procedures.h"

int WINAPI WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR args, _In_ int ncmdshow)
{
	WNDCLASSEX window{};
	HWND hwnd;
	MSG messages;

	window.cbSize = sizeof(WNDCLASSEX);
	window.style = 0;
	window.lpfnWndProc = WindowProcedure;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = hInst;
	window.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	window.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	
	window.lpszMenuName = NULL;	
	window.lpszClassName = L"window";
	

	if (!RegisterClassEx(&window))
	{
		MessageBoxEx(NULL, L"ERROR creating window class", L"MASTER ERROR", MB_ICONERROR, 0);
		return -1;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"window", L"WALUTEX", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, 100, 100, 600, 700, NULL, NULL, hInst, NULL);

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