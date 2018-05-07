#pragma once
#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS
//v_tbc_main: view tab control main
#include <Windows.h>
#include <Commctrl.h>
#include "tabName.h"
///--------------------------------------------------------------------------

// Creates a tab control, sized to fit the specified parent window's client
//   area, and adds some tabs. 
// Returns the handle to the tab control. 
// hwndParent - parent window (the application's main window). 
// 
#define MAX_TABS 2
tabName tabNames[MAX_TABS];

HWND DoCreateTabControl(HWND hwndParent, HINSTANCE hInst)
{

	RECT rcClient;
	INITCOMMONCONTROLSEX icex;
	HWND hwndTab; //hola
	TCITEM tie;
	int i;
	TCHAR achTemp[256];  // Temporary buffer for strings.

						 // Initialize common controls.
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;
	InitCommonControlsEx(&icex);


	// Get the dimensions of the parent window's client area, and 
	// create a tab control child window of that size. Note that g_hInst
	// is the global instance handle.
	GetClientRect(hwndParent, &rcClient);
	hwndTab = CreateWindow(WC_TABCONTROL, L"",
		WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
		0, 0, rcClient.right, rcClient.bottom,
		hwndParent, NULL, hInst, NULL);
	if (hwndTab == NULL)
	{
		return NULL;
	}


	// Add tabs for each day of the week. 
	tie.mask = TCIF_TEXT | TCIF_IMAGE;
	tie.iImage = -1;

	//achTemp = TCHAR("Hola");


	//tie.pszText = achTemp;

	
	
	/*
	char tabName00[] = "Filtrado";
	char tabName01[] = "";
	wchar_t wtext[20];
	mbstowcs(wtext, tabName00, strlen(tabName00) + 1);
	LPWSTR textL = wtext;
	*/
	
	tabNames[0].setName("Filtrado");
	tabNames[1].setName("Conteo de personas");

//	tie.pszText = tabNames[0].getNameLPWSTR();

	for (i = 0; i < MAX_TABS; i++)
	{
		// Load the day string from the string resources. Note that
		// g_hInst is the global instance handle.
		/*tie.pszText = LPWSTR("");
		tie.pszText = tabText[i];*/
		tie.pszText = tabNames[i].getNameLPWSTR();

		LoadString(hInst, i, achTemp, sizeof(achTemp) / sizeof(achTemp[0]));
		if (TabCtrl_InsertItem(hwndTab, i, &tie) == -1)
		{
			DestroyWindow(hwndTab);
			return NULL;
		}
		
			
		
	}
	return hwndTab;


}

// Creates a child window (a static control) to occupy the tab control's 
//   display area. 
// Returns the handle to the static control. 
// hwndTab - handle of the tab control. 
// 
HWND DoCreateDisplayWindow(HWND hwndTab, HINSTANCE hInst)
{

	HWND hwndStatic = CreateWindow(WC_STATIC, L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		100, 100, 100, 100,        // Position and dimensions; example only.
		hwndTab, NULL, hInst,    // g_hInst is the global instance handle
		NULL);

	
	
	
	return hwndStatic;

}

// Handles the WM_SIZE message for the main window by resizing the 
//   tab control. 
// hwndTab - handle of the tab control.
// lParam - the lParam parameter of the WM_SIZE message.
//


HRESULT OnSize(HWND hwndTab, LPARAM lParam)
{

	RECT rc;

	if (hwndTab == NULL)
		return E_INVALIDARG;

	// Resize the tab control to fit the client are of main window.
	if (!SetWindowPos(hwndTab, HWND_TOP, 0, 0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), SWP_SHOWWINDOW))
		return E_FAIL;

	

	return S_OK;

}

// Handles notifications from the tab control, as follows: 
//   TCN_SELCHANGING - always returns FALSE to allow the user to select a 
//     different tab.  
//   TCN_SELCHANGE - loads a string resource and displays it in a static 
//     control on the selected tab.
// hwndTab - handle of the tab control.
// hwndDisplay - handle of the static control. 
// lParam - the lParam parameter of the WM_NOTIFY message.
//

BOOL OnNotify(HWND hwndTab, HWND hwndDisplay, LPARAM lParam, HINSTANCE hInst)
{

	TCHAR achTemp[256]; // temporary buffer for strings

	switch (((LPNMHDR)lParam)->code)
	{
	case TCN_SELCHANGING:
	{
		// Return FALSE to allow the selection to change.
		return FALSE;
	}

	case TCN_SELCHANGE:
	{
		int iPage = TabCtrl_GetCurSel(hwndTab);

		// Note that g_hInst is the global instance handle.
		LoadString(hInst, iPage, achTemp,
			sizeof(achTemp) / sizeof(achTemp[0]));
		LRESULT result = SendMessage(hwndDisplay, WM_SETTEXT, 0,
			(LPARAM)achTemp);


		break;
	}
	}
	return TRUE;

	//return 0;
}
