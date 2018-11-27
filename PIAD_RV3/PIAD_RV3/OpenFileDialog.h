#pragma once
//make sure this is commented out in all code (usually stdafx.h)
//#define WIN32_LEAN_AND_MEAN 

#include <windows.h>
#include <tchar.h>  
#include "convert.h"
//#include <commDlg.h>
#include <string>
	
using namespace std;
string getPathToImage(HWND hWnd)
{
	OPENFILENAME ofn;       // common dialog box structure
	CHAR szFile[260];// = { 0 }; // if using TCHAR macros					 // Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = _T("Imagenes BMP\0*.bmp\0 Todos los archivos \0*.*\0");
	ofn.lpstrFilter = _T("Imagenes PNG \0*.png\0 Imagenes BMP\0*.bmp\0 Imagenes JPG \0*.jpg\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		std::string data = std::string(szFile);
		return data;
		//return data;// ofn.lpstrFile;
		
	}
	else
	{
		MessageBox(0, "No se eligió archivo", "Abrir imagen", NULL);
		dbx_filtrado.imagen_obtenida = false;
		return "";
	}
}
string getPathToVideo(HWND hWnd)
{
	OPENFILENAME ofn;       // common dialog box structure
	TCHAR szFile[260];// = { 0 };       // if using TCHAR macros
	//CHAR szFile[MAX_PATH];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = _T("Imagenes BMP\0*.bmp\0 Todos los archivos \0*.*\0");
	ofn.lpstrFilter = _T("Todo \0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		std::string data = std::string(szFile);
		//return ofn.lpstrFile;
		return data;
		/*wstring ws(ofn.lpstrFile);
		string myVarS = string(ws.begin(), ws.end());
		return myVarS;*/
	}
	else
	{
		MessageBox(0, "No se eligió archivo", "Abrir imagen", NULL);
		dbx_filtrado.imagen_obtenida = false;
		return "";
	}

}

string getPathToSaveImage(HWND hWnd)
{
	OPENFILENAME ofn;       // common dialog box structure
	TCHAR szFile[260] = { 0 };       // if using TCHAR macros
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
		std::string data = std::string(szFile) + ".png";
		//return ofn.lpstrFile;
		return data;
	}
	else
	{
		MessageBox(0, "No se eligió archivo", "Abrir imagen", NULL);
		dbx_filtrado.imagen_obtenida = false;
		return "";
	}
}
