#pragma once
//make sure this is commented out in all code (usually stdafx.h)
//#define WIN32_LEAN_AND_MEAN 

#include <windows.h>
#include <tchar.h>  
#include "convert.h"


OPENFILENAME ofn;       // common dialog box structure
TCHAR szFile[260] = { 0 };       // if using TCHAR macros

								 // Initialize OPENFILENAME
LPCWSTR getPathToImage(HWND hWnd)
{
	
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = _T("Imagenes BMP\0*.bmp\0 Todos los archivos \0*.*\0");
	ofn.lpstrFilter = _T("Imagenes PNG \0*.png\0 Imagenes BMP\0*.bmp\0 Imagenes JPG \0*.jpg\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	else
	{
		MessageBox(0, L"No se eligió archivo", L"Abrir imagen", NULL);
		dbx_filtrado.imagen_obtenida = false;
		return NULL;
	}
	return NULL;
}
LPCWSTR getPathToSave(HWND hWnd)
{

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = _T("Imagenes BMP\0*.bmp\0 Todos los archivos \0*.*\0");
	ofn.lpstrFilter = _T("Imagenes PNG \0*.png\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	else
	{
		MessageBox(0, L"No se eligió archivo", L"Abrir imagen", NULL);
		dbx_filtrado.imagen_obtenida = false;
		return NULL;
	}
	return NULL;
}
