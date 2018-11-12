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
//#include "ctrl_multimedia.h"
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
		
		//b
		
		//g
		
		//r
		
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
void start_record(HWND hWnd, mod_picture image, mod_picture imageFiltrada)
{
	//clase correspondiente a la camara
	//el paraemtro dice que camara de las conectadas
	//es la que se va a leer
	VideoCapture camara(0);

	if (!camara.isOpened())  // si no se pudo ahi muere, lastima!
	{
		cout << "No se pudo abrir la camara" << endl;
		return;
	}
	
	//ciclo infinito para la lectura de la camara
	while (1)
	{
		Mat frame, frame2, gris; //aqui guardaremos el frame
		
		bool exito = camara.read(frame); // lee un frame
		if (!exito) //si no se pudo lastima de nuevo
		{
			cout << "no pude leer!" << endl;
			break;
		}
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
				luminancia(p, q, j, objFiltro.propFiltro[1].activado);
				luminosidad(p, q, j, nCols, objFiltro.propFiltro[2].activado);
				promedio(p, q, j, objFiltro.propFiltro[3].activado);
				sepia(p, q, j, objFiltro.propFiltro[4].activado);
				gausiano(p, q, j, objFiltro.propFiltro[8].activado);

				
			}
		}
		imshow("Imagen sin filtrar", frame);
		imshow("Imagen filtrada", frame2);
		

		

		//crea la ventana y muestralo al mundo!
		//imshow("Mi primer Video", frame2);
		//Mat frameX(frame, Rect(0, 0, 640, 480));
		//imshow("Imagen sin filtrar", frameX);
	
		//hBitmap = CreateBitmap(frame2.cols, frame2.rows, 0, 0, &frame2.data);
		//cvEncodeImage(".bmp", frame2, CV_8UC1, imwrite("foto", frame2, ))
		
		//guardar::guardar_imagen(frame2, hWnd, image);

		//SendDlgItemMessage(hWnd, PIC_VIDEOCAMERA, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		
		//Mat gris2(gris.clone(), Rect(0, 0, 640, 480));
		///equalizeHist(gris, gris);
		//imshow(nombreFiltro, gris);

		//guardar::guardar_imagen(gris, hWnd, imageFiltrada);

		//imshow("Escala de gris", gris2);
		//detecta una tecla, si es el esc entonces fuera
		if (waitKey(16) == 27 || dbx_filtrado.cerrar_dialogo)
		{
			cout << "juimonos!!" << endl;
			break;
		}

	}
}


