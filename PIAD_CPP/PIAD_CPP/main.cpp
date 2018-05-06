// GT_HelloWorldWin32.cpp  
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c  

#define DAYS_IN_WEEK 7
#define IDS_SUNDAY 1
#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  
#include "controls.h"
#include <Commctrl.h>
#include <windowsx.h>

#pragma comment (lib, "Comctl32.lib")

// Global variables  
/*HWND DoCreateTabControl(HWND);
HWND DoCreateDisplayWindow(HWND);
HRESULT OnSize(HWND, LPARAM);
BOOL OnNotify(HWND, HWND, LPARAM);*/
// The main window class name.  
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.  
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

HINSTANCE hInst;
HWND DoCreateTabControl(HWND);
// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable  

					   // The parameters to CreateWindow explained:  
					   // szWindowClass: the name of the application  
					   // szTitle: the text that appears in the title bar  
					   // WS_OVERLAPPEDWINDOW: the type of window to create  
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
					   // 500, 100: initial size (width, length)  
					   // NULL: the parent of this window  
					   // NULL: this application does not have a menu bar  
					   // hInstance: the first parameter from WinMain  
					   // NULL: not used in this application  
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	//_objects::button *btnHola = new _objects::button(&hWnd, L"Hola", 0, 0, 617, 43);
	//_objects::button *btnOtro = new _objects::button(&hWnd, L"otro", 10, 10, 100, 50);
	DoCreateTabControl(hWnd);
	//btnHola.crear(&hWnd, L"hola");

	// Main message loop:  
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//  
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)  
//  
//  PURPOSE:  Processes messages for the main window.  
//  
//  WM_PAINT    - Paint the main window  
//  WM_DESTROY  - post a quit message and return  
//  
//  
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, World!");

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Here your application is laid out.  
		// For this introduction, we just print out "Hello, World!"  
		// in the top left corner.  
		TextOut(hdc,
			5, 5,
			greeting, _tcslen(greeting));
		// End application-specific layout section.  

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

///--------------------------------------------------------------------------


// Creates a tab control, sized to fit the specified parent window's client
//   area, and adds some tabs. 
// Returns the handle to the tab control. 
// hwndParent - parent window (the application's main window). 
// 


HWND DoCreateTabControl(HWND hwndParent)
{
	
	RECT rcClient;
	INITCOMMONCONTROLSEX icex;
	HWND hwndTab;
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
	//achTemp = ("Hola");
	tie.pszText = achTemp;
	
	for (i = 0; i < 2; i++)
	{
		// Load the day string from the string resources. Note that
		// g_hInst is the global instance handle.
		LoadString(hInst, IDS_SUNDAY + i,
			achTemp, sizeof(achTemp) / sizeof(achTemp[0]));
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
HWND DoCreateDisplayWindow(HWND hwndTab)
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

BOOL OnNotify(HWND hwndTab, HWND hwndDisplay, LPARAM lParam)
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
		LoadString(hInst, IDS_SUNDAY + iPage, achTemp,
			sizeof(achTemp) / sizeof(achTemp[0]));
		LRESULT result = SendMessage(hwndDisplay, WM_SETTEXT, 0,
			(LPARAM)achTemp);
		break;
	}
	}
	return TRUE;
	
	//return 0;
}

