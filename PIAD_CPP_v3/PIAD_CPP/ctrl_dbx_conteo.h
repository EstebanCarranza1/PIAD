#pragma once
#include <Windows.h>
#include "resource.h"
#include "OpenFileDialog.h"
#include "mod.picture.h"
#include "e4.h"

mod_picture picConteo;

LRESULT CALLBACK call_conteo(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{

		HWND hPicConteo = GetDlgItem(hWnd, PIC_VIDEOCAMERA);
		
		picConteo.setSize(640, 480);
		picConteo.setPathDefault("config\\gamma.bmp");
		picConteo.id = PIC_VIDEOCAMERA;
		

		picConteo.setImagen((HBITMAP)LoadImage(NULL, convertCharArrayToLPCWSTR(picConteo.getPath()), IMAGE_BITMAP, picConteo.getSizeWidth(), picConteo.getSizeHeight(), LR_LOADFROMFILE));
		SendDlgItemMessage(hWnd, picConteo.id, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)picConteo.getImagen());

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

			e4(hWnd, picConteo);
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