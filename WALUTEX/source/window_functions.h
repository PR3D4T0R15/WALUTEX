#pragma once

//buttons
#define hmenu_exitButton 001
#define hmenu_saveButton 002
#define hmenu_aboutButton 003

#define converterBaseCurrencyCombobox 1001
#define converterBaseCurrencyField 1002
#define converterBaseFlag 1003
#define converterConvertedCurrencyCombobox 2001
#define converterConvertedCurrencyField 2002
#define converterConvertedFlag 2002
#define converterConvertButton 1000

//list
#define listWindow 2000

void CreateMainControls(HWND);
void CreateListData();
void ChangeFlag();

struct currenciesStruct
{
	double Bid;
	double Ask;
	const wchar_t* code;
	const wchar_t* name;
};
