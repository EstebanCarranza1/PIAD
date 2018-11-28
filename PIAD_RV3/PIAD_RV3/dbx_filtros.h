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
	//imagen de camara o de archivo
	bool guardar_img_filtrada = false;
	bool guardar_img_original = false;
	//video de camara
	bool guardar_vid_filtrada = false;
	bool guardar_vid_original = false;
	//video de archivo
	bool guardar_vid_filtrada_archivo = false;
	bool guardar_vid_original_archivo = false;
	//estado actual de grabación camara
	int estado_vid_original = 0;
	int estado_vid_filtrada = 0;
	//estado actual de grabación archivo
	int estado_vid_desde_archivo_filtrado = false;
	int estado_vid_desde_archivo_original = false;
	//conteo de personas
	int personas_detectadas = 0;
	//virtual LRESULT CALLBACK callback(HWND, UINT, WPARAM, LPARAM);
};
