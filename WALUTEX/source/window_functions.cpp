#include <windows.h>
#include "window_functions.h"

//menu hwnd
HMENU hMenu;
//converter hwnd
HWND baseCurrency, baseCurrencyAmount, convertedCurrency, convertedCurrencyAmount, convertButton;


void CreateMainControls(HWND hwnd)
{
	hMenu = CreateMenu();
	HMENU hMenu1 = CreateMenu();
	HMENU hMenu2 = CreateMenu();

	//hmenu setup
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu1, L"Plik");
		AppendMenu(hMenu1, MF_STRING, hmenu_saveButton, L"Zapisz do pliku");
		AppendMenu(hMenu1, MF_STRING, hmenu_exitButton, L"WYJŒCIE");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu2, L"Pomoc");
		AppendMenu(hMenu2, MF_STRING, hmenu_aboutButton, L"O programie");
	SetMenu(hwnd, hMenu);

	//converter setup
	baseCurrency = CreateWindowEx(WS_EX_CLIENTEDGE, L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN, 10, 20, 100, 300, hwnd, (HMENU)converterBaseCurrencyCombobox, NULL, NULL);
	baseCurrencyAmount = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 20, 100, 60, hwnd, (HMENU)converterBaseCurrencyField, NULL, NULL);
	convertedCurrency = CreateWindowEx(WS_EX_CLIENTEDGE, L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN, 260, 20, 100, 300, hwnd, (HMENU)converterConvertedCurrencyCombobox, NULL, NULL);
	convertedCurrencyAmount = CreateWindowEx(NULL, L"STATIC", L"10 USD = 24.6 PLN", WS_CHILD | WS_VISIBLE, 20, 100, 500, 50, hwnd, (HMENU)converterConvertedCurrencyField, NULL, NULL);
	convertButton = CreateWindowEx(NULL, L"BUTTON", L"PRZELICZ", WS_CHILD | WS_VISIBLE, 80, 170, 200, 30, hwnd, (HMENU)converterConvertButton, NULL, NULL);



	//TODO:listview do wyswletlania kursow
}
