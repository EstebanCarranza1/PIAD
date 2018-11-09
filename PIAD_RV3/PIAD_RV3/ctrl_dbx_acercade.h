#pragma once
#pragma once
#include <Windows.h>
#include "resource.h"

HWND lbx_acercade;


LRESULT CALLBACK call_acercade(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		//hWnd_dbx_console = hWnd;
		
		lbx_acercade = GetDlgItem(hWnd, LBX_ACERCADE);
		SendMessageA(lbx_acercade, LB_INSERTSTRING, 0, (LPARAM)"ESTEBAN CARRANZA");
		SendMessageA(lbx_acercade, LB_INSERTSTRING, 0, (LPARAM)"UNIVERSIDAD AUTONOMA DE NUEVO LEÓN");
		SendMessageA(lbx_acercade, LB_INSERTSTRING, 0, (LPARAM)"FACULTAD DE CIENCIAS FISICO MATEMATICAS");
		SendMessageA(lbx_acercade, LB_INSERTSTRING, 0, (LPARAM)"LICENCIATURA MULTIMEDIA Y ANIMACIÓN DIGITAL");
		SendMessageA(lbx_acercade, LB_INSERTSTRING, 0, (LPARAM)"PROCESAMIENTO DE IMAGENES Y DIALOGOS");
	
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