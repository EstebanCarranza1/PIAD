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
#include "guardar_imagen.h"

#pragma comment(lib,"opencv_world310d.lib")



using namespace cv;
using namespace std;
HBITMAP hBitmap;

HBITMAP cambiarPic()
{
	HBITMAP hBitmapX;
	hBitmapX = (HBITMAP)LoadImage(NULL, L"C:\\DATA\\02.bmp", IMAGE_BITMAP, 640, 480, LR_LOADFROMFILE);
	return hBitmapX;
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
		cvtColor(frame2, gris, CV_BGR2GRAY);
		//obtenemos las filas de la imagen
		int nRows = frame.rows;
		//las columnas efectivas de la imagen
		int nCols = frame.cols * channels;

		int i, j, k = 0;
		//punteros para manejar a la imagen
		uchar *p, *q;
		for (i = 0; i < nRows; ++i)
		{
			p = frame.ptr<uchar>(i);
			q = frame2.ptr<uchar>(i);

			for (j = 0; j < nCols; j += 3)
			{
				q[j] = p[j];
				q[j + 1] = p[j + 1];
				q[j + 2] = p[j + 2];
			}
		}


		//crea la ventana y muestralo al mundo!
		//imshow("Mi primer Video", frame2);
		Mat frameX(frame, Rect(0, 0, 1, 1));
		imshow("No me repruebe por hacer esto por favor :'v", frameX);
	
		//hBitmap = CreateBitmap(frame2.cols, frame2.rows, 0, 0, &frame2.data);
		//cvEncodeImage(".bmp", frame2, CV_8UC1, imwrite("foto", frame2, ))
		
		guardar::guardar_imagen(frame2, hWnd, image);

		//SendDlgItemMessage(hWnd, PIC_VIDEOCAMERA, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	
		Mat gris2 = gris.clone();
		equalizeHist(gris, gris);
		//imshow("Escala de gris equalizado", gris);

		guardar::guardar_imagen(gris, hWnd, imageFiltrada);

		//imshow("Escala de gris", gris2);
		//detecta una tecla, si es el esc entonces fuera
		if (waitKey(16) == 27 || dbx_filtrado.cerrar_dialogo)
		{
			cout << "juimonos!!" << endl;
			break;
		}

	}
}