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
	//virtual LRESULT CALLBACK callback(HWND, UINT, WPARAM, LPARAM);
};
