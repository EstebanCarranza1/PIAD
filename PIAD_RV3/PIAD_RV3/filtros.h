#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include "resource.h"
#include <math.h>
#include "convert.h"
#include "dbx_filtros.h"
#include "mod.picture.h"
#include "mod.filtro.h"
#include "ctrl_multimedia.h"
#include "mod.saveData.h"

//#pragma comment(lib,"opencv_world310d.lib")


using namespace cv;
using namespace std;
HBITMAP hBitmap;

HWND hWnd_dbx_console;
HWND hWnd_dbx_filtros;

/*
HBITMAP cambiarPic()
{
	HBITMAP hBitmapX;
	hBitmapX = (HBITMAP)LoadImage(NULL, L"C:\\DATA\\02.bmp", IMAGE_BITMAP, 640, 480, LR_LOADFROMFILE);
	return hBitmapX;
}*/
string nombreFiltro = "Filtros";
int saturacion = 255;
int corte = 0;

void corte_saturacion(int *valor)
{
	if (*valor > saturacion)
		*valor = saturacion;
	else if (*valor < corte)
		*valor = corte;
}
void copia(uchar *p, uchar *q, int j)
{
	q[j] = p[j];
	q[j + 1] = p[j + 1];
	q[j + 2] = p[j + 2];
}
void promedio(uchar *p, uchar *q, int j, bool activar)
{
	if(activar)
	{
		nombreFiltro = "Promedio";
		//b
		q[j] = ((p[j] + p[j + 1] + p[j + 2]) / 3);
		//g
		q[j + 1] = ((p[j] + p[j + 1] + p[j + 2]) / 3);
		//r		   
		q[j + 2] = ((p[j] + p[j + 1] + p[j + 2]) / 3);
	}
}

void luminosidad(uchar *p, uchar *q, int j, int nCols, bool activar)
{
	if (activar)
	{
		uchar maxRGB = 0;
		uchar minRGB = 0;

		if (p[j] > p[j + 1] && p[j] > p[j + 2])
			maxRGB = p[j];
		else if (p[j + 1] > p[j] && p[j + 1] > p[j + 2])
			maxRGB = p[j + 1];
		else if (p[j + 2] > p[j] && p[j + 2] > p[j + 1])
			maxRGB = p[j + 2];

		if (p[j] < p[j + 1] && p[j] < p[j + 2])
			minRGB = p[j];
		else if (p[j + 1] < p[j] && p[j + 1] < p[j + 2])
			minRGB = p[j + 1];
		else if (p[j + 2] < p[j] && p[j + 2] < p[j + 1])
			minRGB = p[j + 2];


		//b
		q[j] = (maxRGB + minRGB) / 2;
		//g
		q[j+1] = (maxRGB + minRGB) / 2;
		//r
		q[j+2] = (maxRGB + minRGB) / 2;
	}
}
void luminancia(uchar *p, uchar *q, int j, bool activar)
{
	if (activar)
	{
		nombreFiltro = "Luminancia";
		
	
		//b
		q[j] = (p[j] * 0.11) + (p[j + 1] * 0.59) + (p[j + 2] * 0.30);
		//g
		q[j + 1] = (p[j] * 0.11) + (p[j + 1] * 0.59) + (p[j + 2] * 0.30);
			//r		   
		q[j + 2] = (p[j] * 0.11) + (p[j + 1] * 0.59) + (p[j + 2] * 0.30);
		
	}
}
void sepia(uchar *p, uchar *q, int j, bool activar)
{
	if (activar)
	{
		nombreFiltro = "Sepia";
		int valBlue =		((p[j + 2] * 0.272) + (p[j + 1] * 0.534) + (p[j] * 0.131));
		int valGreen =	((p[j + 2] * 0.349) + (p[j + 1] * 0.686) + (p[j] * 0.168));
		int valRed =		((p[j + 2] * 0.393) + (p[j + 1] * 0.769) + (p[j] * 0.189));

		corte_saturacion(&valBlue);
		corte_saturacion(&valGreen);
		corte_saturacion(&valRed);
		
		//b
		q[j] = valBlue;
		//g
		q[j + 1] = valGreen;
		//r		   
		q[j + 2] = valRed;
	}
}
void gausiano(uchar *p, uchar *q, int j, bool activar)
{
	if (activar)
	{
		nombreFiltro = "Sepia";
		int valBlue =	((p[j + 2] + 1) +		(p[j + 1] + 2) + (p[j] + 1));
		int valGreen =	((p[j + 2] + 2) +	(p[j + 1] + 7) + (p[j] + 2));
		int valRed =	((p[j + 2] + 1) +		(p[j + 1] + 2) + (p[j] + 1));

		corte_saturacion(&valBlue);
		corte_saturacion(&valGreen);
		corte_saturacion(&valRed);

		//b
		q[j] = valBlue;
		//g
		q[j + 1] = valGreen;
		//r		   
		q[j + 2] = valRed;
	}
}

bool ventana_abierta = false;
void cargar_imagen(cv::String path)
{
	
	Mat frame;
	frame = imread(path, CV_LOAD_IMAGE_COLOR);
	if (frame.data)
	{
		namedWindow("Imagen estatica", WINDOW_AUTOSIZE);
		imshow("Imagen estatica", frame);
		waitKey(0);

	}
	else
		MessageBoxA(0, "No se pudo cargar la imagen :c", "", 0);
}
bool cameraOpen = false;
void filtrar(Mat frame, Mat frame2, int formaFiltrado)
{
	
		//de lo leido por la camara obtenemos la cantidad de
		//canales, 3 por ser rgb
		int channels = frame.channels();
		//clonamos al frame leido con la intencion de obtener
		//sus caracteristicas de ancho, alto, canales
		frame2 = frame.clone();
		//convertimos a gris para manejar un solo canal
		//cvtColor(frame2, gris, CV_BGR2GRAY);
		//obtenemos las filas de la imagen
		int nRows = frame.rows;
		//las columnas efectivas de la imagen
		int nCols = frame.cols * channels;

		int i, j, k = 0;

		//punteros para manejar a la imagen
		uchar *p, *q;
		for (i = 0; i < nRows; i++)
		{
			p = frame.ptr<uchar>(i);
			q = frame2.ptr<uchar>(i);

			for (j = 0; j < nCols; j += 3)
			{
				copia(p, q, j);
				luminancia(p, q, j, objFiltro.propFiltro[objFiltro.flt_luminancia].activado);
				luminosidad(p, q, j, nCols, objFiltro.propFiltro[objFiltro.flt_luminosidad].activado);
				promedio(p, q, j, objFiltro.propFiltro[objFiltro.flt_promedio].activado);
				sepia(p, q, j, objFiltro.propFiltro[objFiltro.flt_sepia].activado);
				gausiano(p, q, j, objFiltro.propFiltro[objFiltro.flt_gaussiano].activado);


			}
		}
		
		imshow("Imagen sin filtrar", frame);
		if (formaFiltrado != objFiltro.reconocimiento_de_personas)
			imshow("Imagen filtrada", frame2);
		
		if (objFiltro.cargar_imagen_desde_archivo || objFiltro.cargar_imagen_desde_camara)
		{
			if (dbx_filtrado.guardar_img_original)
			{
				dbx_filtrado.guardar_img_original = false;
				LPCWSTR path = getPathToSave(0);
				if (path != NULL)
				{
					char pathCHAR[255];
					strcpy_s(pathCHAR, convertLPCWSTRtoCHAR(path));
					mod_multimedia::imagen::SaveOfPC(frame, pathCHAR);
					
					MessageBoxA(0, "La imagen original fue guardada con exito", "Guardar imagen", 0);
				}
				else
					MessageBoxA(0, "Elegir donde quiere guardar la imagen", "Guardar imagen", 0);
				
				
			}
			else if (dbx_filtrado.guardar_img_filtrada)
			{
				dbx_filtrado.guardar_img_filtrada = false;
				LPCWSTR path = getPathToSave(0);
				if (path != NULL)
				{
					char pathCHAR[255];
					strcpy_s(pathCHAR, convertLPCWSTRtoCHAR(path));
					mod_multimedia::imagen::SaveOfPC(frame2, pathCHAR);
					MessageBoxA(0, "La imagen original fue guardada con exito", "Guardar imagen", 0);
				}
				else
					MessageBoxA(0, "Elegir donde quiere guardar la imagen", "Guardar imagen", 0);

			}
		}
		
	
	

}
void obtener_imagen_archivo(char path[255], int formaFiltrado)
{
	dbx_filtrado.cerrar_dialogo = false;
	bool iniciar_filtrado = false;
	Mat frame, frame2;
	Mat resize;
	frame = NULL; frame2 = NULL;
	frame = mod_multimedia::imagen::LoadOfPC(path);
	if (frame.dims > 0)
	{
		cv::resize(frame, resize, Size(640, 480), 0, 0, INTER_CUBIC);
		frame = NULL;
		frame = resize.clone();
		iniciar_filtrado = true;
	}
	else
	{
		dbx_filtrado.cerrar_dialogo = true;
		MessageBoxA(0, "Esta imagen no se puede cargar correctamente, verifique que la dirección o el nombre de la imagen no sean muy largos y/o que estén guardadas con el formato apropiado", "Carga de imagen", 0);
	}
	dbx_filtrado.cerrar_dialogo = false;

	while (iniciar_filtrado)
	{
		
			filtrar(frame, frame2, formaFiltrado);
		
		if (waitKey(16) == 27 || dbx_filtrado.cerrar_dialogo)
		{
			cvDestroyWindow("Imagen sin filtrar");
			cvDestroyWindow("Imagen filtrada");
			break;
		}
	}
}
void obtener_imagen_desde_camara()
{
	dbx_filtrado.cerrar_dialogo = false;
	Mat frame, frame2;
	VideoCapture camara(0);
	if (!camara.isOpened())  // si no se pudo ahi muere, lastima!
	{
		cout << "No se pudo abrir la camara" << endl;
		return;
	}
	while (1)
	{
		if (!dbx_filtrado.capturar)
		{
			bool exito = camara.read(frame); // lee un frame
			if (!exito) //si no se pudo lastima de nuevo
			{
				cout << "no pude leer!" << endl;
				break;
			}
		}
		filtrar(frame, frame2, objFiltro.cargar_imagen_desde_camara);
		
		if (waitKey(16) == 27 || dbx_filtrado.cerrar_dialogo)
		{
			cvDestroyWindow("Imagen sin filtrar");
			cvDestroyWindow("Imagen filtrada");
			camara.release();
			break;
		}
	}
}
void start_record(HWND hWnd, mod_picture image, mod_picture imageFiltrada, int formaFiltrado,char path[255])
{
	
	/*
	//ciclo infinito para la lectura de la camara
	while (1)
	{
		Mat frame, frame2; //aqui guardaremos el frame
		if(
			(formaFiltrado == objFiltro.cargar_imagen_desde_camara) ||
			(formaFiltrado == objFiltro.cargar_video_desde_camara)
			)
		{
		
				VideoCapture camara(0);
				if (!camara.isOpened())  // si no se pudo ahi muere, lastima!
				{
					cout << "No se pudo abrir la camara" << endl;
					return;
				}
			
			bool exito = camara.read(frame); // lee un frame
			if (!exito) //si no se pudo lastima de nuevo
			{
				cout << "no pude leer!" << endl;
				break;
			}
		}else if (formaFiltrado == objFiltro.cargar_imagen_desde_archivo)
		{
			
			frame = mod_multimedia::imagen::LoadOfPC(path);
		}
		
		imshow("Imagen sin filtrar", frame);
		if (formaFiltrado != objFiltro.reconocimiento_de_personas)
			imshow("Imagen filtrada", frame2);
		

	
		if (waitKey(16) == 27 || dbx_filtrado.cerrar_dialogo)
		{
			cout << "juimonos!!" << endl;
			break;
		}

	}*/
}


