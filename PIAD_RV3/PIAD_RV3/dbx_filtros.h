#pragma once
#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
//#include "convert.h"

class mod_dialogBox
{
	public:
	HWND hWnd;
	HINSTANCE hInst;
	bool cerrar_dialogo = false;
	bool capturar = false;
	bool imagen_obtenida = false;
	bool guardar_img_filtrada = false;
	bool guardar_img_original = false;
	//virtual LRESULT CALLBACK callback(HWND, UINT, WPARAM, LPARAM);
};
