#pragma once
#ifndef filtro
#define filtro
#include "paletas.h"

static class filtros
{
public:
	static class F_GRAY_SCALE
	{

	};

	static class F_RGB
	{
	public:
		static float luminosidad(RGB *colorMax, RGB *colorMin)
		{
			float lum;

			lum =
				(
					(colorMax->blue	 + colorMin->blue) + 
					(colorMax->green + colorMin->green) +
					(colorMax->red	 + colorMin->red)
				)/2;
			
			return lum;
		}
		static float promedio(RGB *color)
		{
			float prom;
			
			prom = (color->red + color->blue + color->green)/3;

			return prom;
		}
		static float luminancia(RGB *color)
		{
			float lum;

			lum = (0.3*color->red) + (0.59*color->green) + (0.11 * color->blue);

			return lum;
		}
		static RGB sepia(RGB *color)
		{
			color->red		= (color->red * 0.393) + (color->green * 0.769) + (color->blue * 0.189);
			color->green	= (color->red * 0.349) + (color->green * 0.686) + (color->blue * 0.168);
			color->blue		= (color->red * 0.272) + (color->green * 0.534) + (color->blue * 0.131);

			return *color;
		}

	};

	static class F_MEDIA
	{
		public:
		
			static int inicializar_mascara(float *matriz, int matrizX, int matrizY, float valMasc)
			{
				static int i = 0;
				for (i = 0; i < ((matrizX * matrizY)); i++)
						*(matriz + i) = valMasc;

				return (matrizX * matrizY);
			}

			static int media
			(
				float *mascara, int mMatrizX, int mMatrizY,
				float *pixel, int pMatrizX, int pMatrizY
			)
			{
				float pixelMedio = 0;
				if ((mMatrizX * mMatrizY) == 9)
				{
					if ((pMatrizX * pMatrizX) >= (mMatrizY * mMatrizY))
					{
						pixelMedio = *(pixel + 2);
					}
				}
				
				return pixelMedio;
			}
	};
};


#endif // !filtro
