#pragma once
#include <Windows.h>
#include "resource.h"
#include "convert.h"
#include "dbx_filtros.h"
#include "ejemplos.h"
dbx_filtros::picture picMenu;
dbx_filtros::dbx dbx_menu;


LRESULT CALLBACK call_menu(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{

		HWND hPicMenu = GetDlgItem(hWnd, PIC_FONDO);
		
		picMenu.setSize(640, 480);
		picMenu.setPathDefault("config\\fondo.bmp");
		picMenu.id = PIC_FONDO;
		

		picMenu.setImagen((HBITMAP)LoadImage(NULL, convertCharArrayToLPCWSTR(picMenu.getPath()), IMAGE_BITMAP, picMenu.getSizeWidth(), picMenu.getSizeHeight(), LR_LOADFROMFILE));
		SendDlgItemMessage(hWnd, picMenu.id, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)picMenu.getImagen());


	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case BTN_FILTROS:
				DialogBox(dbx_filtrado.hInst, MAKEINTRESOURCE(DBX_TEST), NULL, reinterpret_cast<DLGPROC>(call_filtrado));
			break;
			case BTN_DATOS:
				e5();
			break;
			case BTN_SALIR:
				exit(0);
			break;
		}
	}
	break;
	}
	return false;
}