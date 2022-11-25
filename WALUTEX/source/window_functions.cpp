#include <windows.h>
#include <commctrl.h>
#include <wchar.h>
#include "window_functions.h"

//menu hwnd
HMENU hMenu;
//converter hwnd
HWND baseCurrency, baseCurrencyAmount, convertedCurrency, convertedCurrencyAmount, convertButton;
//currency list
HWND list;
const wchar_t* currenciesShort[] = { L"USD", L"AUD", L"CAD", L"EUR", L"HUF", L"CHF", L"GBP", L"JPY", L"CZK", L"DKK", L"NOK", L"SEK" };
currencies currenciesData[12];
LVITEM listItems[12];


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

	//currency list
	RECT rcl;
	GetClientRect(hwnd, &rcl);
	list = CreateWindowEx(NULL, WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT, 0, 200, rcl.right - rcl.left, rcl.bottom - rcl.top, hwnd, (HMENU)listWindow, NULL, NULL);

	LVCOLUMN columns;
	columns.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	columns.iSubItem = 0;
	columns.cx = 200;
	columns.pszText = (LPWSTR)L"NAZWA WALUTY";
	ListView_InsertColumn(list, 0, &columns);

	columns.iSubItem = 0;
	columns.cx = 90;
	columns.pszText = (LPWSTR)L"FLAGA";
	ListView_InsertColumn(list, 1, &columns);

	columns.iSubItem = 0;
	columns.cx = 90;
	columns.pszText = (LPWSTR)L"KOD";
	ListView_InsertColumn(list, 2, &columns);

	columns.iSubItem = 0;
	columns.cx = 100;
	columns.pszText = (LPWSTR)L"KUP";
	ListView_InsertColumn(list, 3, &columns);

	columns.iSubItem = 0;
	columns.cx = 100;
	columns.pszText = (LPWSTR)L"SPRZEDA¯";
	ListView_InsertColumn(list, 4, &columns);




	//TODO:listview do wyswletlania kursow
}

void CreateListData()
{
	const wchar_t* currenciesLong[] = { L"dolar amerykañski", L"dolar australijski", L"dolar kanadyjski", L"euro", L"forint", L"frank szwajcarski", L"funt szterling", L"jen", L"korona czeska", L"korona duñska", L"korona norweska", L"korona szwedzka" };

	for (int i = 0; i < 12; i++)
	{
		currenciesData[i].code = currenciesShort[i];
		currenciesData[i].name = currenciesLong[i];
		currenciesData[i].Ask = 0.0;
		currenciesData[i].Bid = 0.0;
	}

	for (int j = 0; j < 12; j++)
	{
		listItems[j].mask = LVIF_TEXT | LVIF_IMAGE;

		listItems[j].pszText = (LPWSTR)currenciesData[j].name;
		listItems[j].iItem = j;
		listItems[j].iSubItem = 0;
		ListView_InsertItem(list, &listItems[j]);

		//ListView_SetItemText(list, j, 1, (LPWSTR)L"test"); - OBRAZEK
		ListView_SetItemText(list, j, 2, (LPWSTR)currenciesData[j].code);

		WCHAR buffer[9];
		swprintf(buffer, 8, L"%f", currenciesData[j].Bid);
		ListView_SetItemText(list, j, 3, (LPWSTR)buffer);

		swprintf(buffer, 8, L"%f", currenciesData[j].Ask);
		ListView_SetItemText(list, j, 4, (LPWSTR)buffer);

	}
	
}
