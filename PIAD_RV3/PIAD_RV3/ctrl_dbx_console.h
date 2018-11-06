#pragma once
#include <Windows.h>
#include "resource.h"

HWND lbx_console;

LRESULT CALLBACK call_console(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			hWnd_dbx_console = hWnd;
			lbx_console = GetDlgItem(hWnd, LBX_CONSOLE);
			SendMessageA(lbx_console, LB_INSERTSTRING, 0, (LPARAM)"CONSOLE OK");

			break;
		}
		case WM_CLOSE:
		{
			EndDialog(hWnd, true);
			break;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
	
				case IDCANCEL:
				{
					EndDialog(hWnd, true);
					break;
				}
		
			}
			break;
		}
	}
	return false;
}