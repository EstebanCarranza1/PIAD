#pragma once
#include <Windows.h>
#include "resource.h"
#include "OpenFileDialog.h"
#include "mod.resolucion.h"

//#include "e4.h"

//mod_picture picConteo;
HWND cbx_resolucion;

LRESULT CALLBACK call_conteo(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		cbx_resolucion = GetDlgItem(hWnd, CBX_RESOLUCION);
		//HWND hPicConteo = GetDlgItem(hWnd, PIC_VIDEOCAMERA);
		for (int i = 0; i < objResolucion.total; i++)
		{
			SendMessageA(cbx_resolucion, CB_ADDSTRING, 0, (LPARAM)objResolucion.values[i].nombre);
		}
		/*SendMessageA(cbx_resolucion, CB_ADDSTRING, 0, (LPARAM)"144p (256x144)");
		SendMessageA(cbx_resolucion, CB_ADDSTRING, 0, (LPARAM)"240p (426x240)");
		SendMessageA(cbx_resolucion, CB_ADDSTRING, 0, (LPARAM)"360p (640x360)");
		SendMessageA(cbx_resolucion, CB_ADDSTRING, 0, (LPARAM)"480p (854x480)");
		SendMessageA(cbx_resolucion, CB_ADDSTRING, 0, (LPARAM)"720p (1280x720)");*/
		SendMessageA(cbx_resolucion, CB_SETCURSEL, 3, 0);

	}
	break;
	case WM_CLOSE:
		dbx_conteo.cerrar_dialogo = true;
		EndDialog(hWnd, true);
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BTN_INICIAR_CAMARA:

			//e4(hWnd, picConteo);
			//imgMnt = cambiarPic();
			//SendDlgItemMessage(hWnd, PIC_VIDEOCAMERA, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imgMnt);
			break;
		case IDCANCEL:
			dbx_conteo.cerrar_dialogo = true;
			EndDialog(hWnd, true);
			break;
		

		}
	}
	break;
	}
	return false;
}