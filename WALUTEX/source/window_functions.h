#pragma once

//buttons
#define hmenu_exitButton 001
#define hmenu_saveButton 002
#define hmenu_aboutButton 003

#define converterBaseCurrencyCombobox 1001
#define converterBaseCurrencyField 1002
#define converterConvertedCurrencyCombobox 1003
#define converterConvertedCurrencyField 1003
#define converterConvertButton 1000

//list
#define listWindow 2000

void CreateMainControls(HWND);
void CreateListData();

struct currencies
{
	double Bid;
	double Ask;
	const wchar_t* code;
	const wchar_t* name;
};
