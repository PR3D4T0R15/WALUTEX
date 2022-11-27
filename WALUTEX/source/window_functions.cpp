#include <windows.h>
#include <commctrl.h>
#include <wchar.h>
#include "window_functions.h"
#include <string>

//menu hwnd
HMENU hMenu;
//converter hwnd
HWND baseCurrency, baseCurrencyAmount, convertedCurrency, convertedCurrencyAmount, convertButton, baseImage, convertedImage;
HBITMAP flags[13];
//currency list
HWND list;
const wchar_t* currenciesShort[13] = { L"USD", L"AUD", L"CAD", L"EUR", L"HUF", L"CHF", L"GBP", L"JPY", L"CZK", L"DKK", L"NOK", L"SEK", L"PLN"};
currenciesStruct currenciesData[13];
LVITEM listItems[13];


void CreateMainControls(HWND hwnd)
{
	hMenu = CreateMenu();
	HMENU hMenu1 = CreateMenu();
	HMENU hMenu2 = CreateMenu();

	for (int i = 0; i < 13; i++)
	{
		std::wstring link = L"source\\img\\flags\\" + std::to_wstring(i) + L".bmp";
		flags[i] = (HBITMAP)LoadImage(NULL, (LPCWSTR)link.c_str(), IMAGE_BITMAP, 100, 50, LR_LOADFROMFILE);
	}

	//hmenu setup
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu1, L"Plik");
		AppendMenu(hMenu1, MF_STRING, hmenu_saveButton, L"Zapisz do pliku");
		AppendMenu(hMenu1, MF_STRING, hmenu_updateData, L"Aktualizuj kurs");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenu2, L"Pomoc");
		AppendMenu(hMenu2, MF_STRING, hmenu_aboutButton, L"O programie");
	SetMenu(hwnd, hMenu);

	//converter setup
	baseCurrency = CreateWindowEx(WS_EX_CLIENTEDGE, L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN, 10, 20, 100, 300, hwnd, (HMENU)converterBaseCurrencyCombobox, NULL, NULL);
	baseCurrencyAmount = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 20, 100, 24, hwnd, (HMENU)converterBaseCurrencyField, NULL, NULL);
	baseImage = CreateWindowEx(NULL, L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP | WS_BORDER, 10, 60, 100, 50, hwnd, (HMENU)converterBaseFlag, NULL, NULL);

	convertedCurrency = CreateWindowEx(WS_EX_CLIENTEDGE, L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN, 370, 20, 100, 300, hwnd, (HMENU)converterConvertedCurrencyCombobox, NULL, NULL);
	convertedCurrencyAmount = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 20, 100, 24, hwnd, (HMENU)converterConvertedCurrencyField, NULL, NULL);
	convertedImage = CreateWindowEx(NULL, L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP | WS_BORDER, 370, 60, 100, 50, hwnd, (HMENU)converterConvertedFlag, NULL, NULL);

	convertButton = CreateWindowEx(NULL, L"BUTTON", L"PRZELICZ", WS_CHILD | WS_VISIBLE, 190, 160, 200, 30, hwnd, (HMENU)converterConvertButton, NULL, NULL);

	for (int i = 0; i < 13; i++)
	{
		SendMessage(baseCurrency, CB_ADDSTRING, NULL, (LPARAM)currenciesShort[i]);
		SendMessage(convertedCurrency, CB_ADDSTRING, NULL, (LPARAM)currenciesShort[i]);
	}
	SendMessage(baseCurrency, CB_SETCURSEL, 2, 0);
	SendMessage(convertedCurrency, CB_SETCURSEL, 2, 0);
	
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
	columns.pszText = (LPWSTR)L"KOD";
	ListView_InsertColumn(list, 1, &columns);

	columns.iSubItem = 0;
	columns.cx = 100;
	columns.pszText = (LPWSTR)L"KUPNO [z³]";
	ListView_InsertColumn(list, 2, &columns);

	columns.iSubItem = 0;
	columns.cx = 100;
	columns.pszText = (LPWSTR)L"SPRZEDA¯ [z³]";
	ListView_InsertColumn(list, 3, &columns);
}

void CreateListData()
{
	const wchar_t* currenciesLong[13] = { L"dolar amerykañski", L"dolar australijski", L"dolar kanadyjski", L"euro", L"forint", L"frank szwajcarski", L"funt szterling", L"jen", L"korona czeska", L"korona duñska", L"korona norweska", L"korona szwedzka", L"z³oty"};

	for (int i = 0; i < 13; i++)
	{
		currenciesData[i].code = currenciesShort[i];
		currenciesData[i].name = currenciesLong[i];
		currenciesData[i].Ask = 0.0;
		currenciesData[i].Bid = 0.0;
	}

	for (int j = 0; j < 12; j++)
	{
		listItems[j].mask = LVIF_TEXT;

		listItems[j].pszText = (LPWSTR)currenciesData[j].name;
		listItems[j].iItem = j;
		listItems[j].iSubItem = 0;
		ListView_InsertItem(list, &listItems[j]);

		ListView_SetItemText(list, j, 1, (LPWSTR)currenciesData[j].code);

		WCHAR buffer[9];
		swprintf(buffer, 8, L"%f", currenciesData[j].Bid);
		ListView_SetItemText(list, j, 2, (LPWSTR)buffer);

		swprintf(buffer, 8, L"%f", currenciesData[j].Ask);
		ListView_SetItemText(list, j, 3, (LPWSTR)buffer);
	}
	
}

void ChangeFlag()
{
	int option1 = SendMessage(baseCurrency, CB_GETCURSEL, 0, 0);
	SendMessage(baseImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)flags[option1]);
	int option2 = SendMessage(convertedCurrency, CB_GETCURSEL, 0, 0);
	SendMessage(convertedImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)flags[option2]);

	SetWindowText(baseCurrencyAmount, NULL);
	SetWindowText(convertedCurrencyAmount, NULL);
}


void UpdateListData()
{
	for (int j = 0; j < 12; j++)
	{
		WCHAR buffer[9];
		swprintf(buffer, 8, L"%f", currenciesData[j].Bid);
		ListView_SetItemText(list, j, 2, (LPWSTR)buffer);

		swprintf(buffer, 8, L"%f", currenciesData[j].Ask);
		ListView_SetItemText(list, j, 3, (LPWSTR)buffer);
	}

	ListView_RedrawItems(list, 0, 12);
}

void CalculateCurrency()
{
	int optionBase = SendMessage(baseCurrency, CB_GETCURSEL, 0, 0);
	int optionConverted = SendMessage(convertedCurrency, CB_GETCURSEL, 0, 0);
	WCHAR buffer[10];
	GetWindowText(baseCurrencyAmount, buffer, 10);
	float baseAmount = _wtof(buffer);
	float out;

	if (optionBase == 12)
	{
		out = (int)baseAmount / currenciesData[optionConverted].Bid;
	}
	else if (optionConverted == 12)
	{
		out = (int)baseAmount * currenciesData[optionBase].Ask;
	}
	else
	{
		float toPLN = int(currenciesData[optionBase].Ask * baseAmount);
		out = toPLN / currenciesData[optionConverted].Bid;
	}

	swprintf(buffer, 10, L"%f", out);
	SetWindowText(convertedCurrencyAmount, buffer);
}

void AskForLocation(HWND hwnd)
{
	OPENFILENAME ofn;
	char fileName[100] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = (LPWSTR)fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"txt";

	if (GetSaveFileName(&ofn))
	{
		// Do something usefull with the filename stored in szFileName 
	}
}