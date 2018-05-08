#pragma once
#include <Windows.h>
#include "resource.h"
#include "OpenFileDialog.h"
#include "e1.h"
#include "mod.picture.h"

mod_picture picNormal, picFiltrada;

LRESULT CALLBACK call_filtrado(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{

		HWND hPicNormal = GetDlgItem(hWnd, PIC_VIDEOCAMERA);
		HWND hPicFiltrada = GetDlgItem(hWnd, PIC_FILTRADA);
		picNormal.setSize(640, 480);
		picNormal.setPathDefault("config\\alpha.bmp");
		picNormal.id = PIC_VIDEOCAMERA;
		picFiltrada.setSize(640, 480);
		picFiltrada.setPathDefault("config\\beta.bmp");
		picFiltrada.id = PIC_FILTRADA;


		picNormal.setImagen((HBITMAP)LoadImage(NULL, convertCharArrayToLPCWSTR(picNormal.getPath()), IMAGE_BITMAP, picNormal.getSizeWidth(), picNormal.getSizeHeight(), LR_LOADFROMFILE));
		SendDlgItemMessage(hWnd, picNormal.id, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)picNormal.getImagen());

		picFiltrada.setImagen((HBITMAP)LoadImage(NULL, convertCharArrayToLPCWSTR(picFiltrada.getPath()), IMAGE_BITMAP, picFiltrada.getSizeWidth(), picFiltrada.getSizeHeight(), LR_LOADFROMFILE));
		SendDlgItemMessage(hWnd, picFiltrada.id, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)picFiltrada.getImagen());

	}
	break;
	case WM_CLOSE:
		dbx_filtrado.cerrar_dialogo = true;
		EndDialog(hWnd, true);
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case BTN_INICIAR_CAMARA:

			start_record(hWnd, picNormal, picFiltrada);
			//imgMnt = cambiarPic();
			//SendDlgItemMessage(hWnd, PIC_VIDEOCAMERA, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imgMnt);
			break;
		case IDCANCEL:
			EndDialog(hWnd, true);
			break;
		case BTN_EXAMINAR:
		{
			LPCWSTR path = getPathToImage(hWnd);
			if (path != NULL)
			{
				picNormal.setImagen((HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 300, 300, LR_LOADFROMFILE));
				SendDlgItemMessage(hWnd, PIC_VIDEOCAMERA, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)picNormal.getImagen());
			}

		}
		break;
		
		}
	}
	break;
	}
	return false;
}