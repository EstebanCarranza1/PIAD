// GT_HelloWorldWin32.cpp  
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c  


#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  
#include "convert.h"
#include "controls.h"
#include <windowsx.h>
#include "v_tbc_main.h";
#include "resource.h"
#include "ctrl_dbx_filtros.h"
#include "ctrl_dbx_conteo.h"
#include "ctrl_dbx_menu.h"
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
HWND TabControl01;
#define btnIrA 100
// Forward declarations of functions included in this code module:  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// <> DIALOGO_1
/*HINSTANCE dbx_dialogo1;
LRESULT CALLBACK call_dialog1(HWND, UINT, WPARAM, LPARAM);*/
//</> DIALOGO_1

//
	
//

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	DialogBox(dbx_menu.hInst, MAKEINTRESOURCE(DBX_MENU), NULL, reinterpret_cast<DLGPROC>(call_menu));
	return 0;
}
/* 
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
		500, 500,
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
	TabControl01 = DoCreateTabControl(hWnd, hInst);
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
	case WM_CREATE:
	{
		HWND hwndButton = CreateWindow(
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"OK",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,         // x position 
			10,         // y position 
			100,        // Button width
			100,        // Button height
			hWnd,     // Parent window
			(HMENU)btnIrA,       // No menu.
			hInst,
			NULL);      // Pointer not needed.

		
	}
	break;
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

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case btnIrA:
			{
				//DialogBox(dbx_dialogo1, MAKEINTRESOURCE(DBX_TEST), hWnd, reinterpret_cast<DLGPROC>(call_dialog1));	
				DialogBox(dbx_menu.hInst, MAKEINTRESOURCE(DBX_MENU), hWnd, reinterpret_cast<DLGPROC>(call_menu));
			}
			break;
		}
	break;
	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}
*/


