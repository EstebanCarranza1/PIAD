#pragma once
#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
static class mod_resolucion
{
	public:
		static const int total = 5;
		struct resolucion
		{
			char nombre[255];
			int horizontal, vertical;
		}values[total];

		void inicializar()
		{
			strcpy_s(values[0].nombre, "144p (256x144)");  values[0].horizontal = 256;  values[0].vertical = 144;
			strcpy_s(values[1].nombre, "240p (426x240)");  values[1].horizontal = 426;  values[1].vertical = 240;
			strcpy_s(values[2].nombre, "360p (640x360)");  values[2].horizontal = 640;  values[2].vertical = 360;
			strcpy_s(values[3].nombre, "480p (854x480)");  values[3].horizontal = 854;  values[3].vertical = 480;
			strcpy_s(values[4].nombre, "720p (1280x720)"); values[4].horizontal = 1280; values[4].vertical = 720;

		}
		mod_resolucion()
		{
			inicializar();
		}

}objResolucion;
//mod_resolucion *objResolucion = new mod_resolucion();