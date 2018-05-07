#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include "resource.h"
#include <math.h>
#include "convert.h"
#include "dbx_filtros.h"


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
int guardar_imagen(Mat mat, HWND hWnd, dbx_filtros::picture image)//HBITMAP hPictureBox, int SizeWidth, int SizeHeight, char pathImg[])
{
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try {
		
		
		imwrite(image.pathDefault, mat, compression_params);
		image.setImagen((HBITMAP)LoadImage(NULL, convertCharArrayToLPCWSTR(image.pathDefault), IMAGE_BITMAP, image.getSizeWidth(), image.getSizeHeight(), LR_LOADFROMFILE));
		SendDlgItemMessage(hWnd, image.id, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image.getImagen());
		
		return 0;
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
		return 1;
	}
}

void start_record(HWND hWnd, dbx_filtros::picture image, dbx_filtros::picture imageFiltrada)
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
	
		//hBitmap = CreateBitmap(frame2.cols, frame2.rows, 0, 0, &frame2.data);
		//cvEncodeImage(".bmp", frame2, CV_8UC1, imwrite("foto", frame2, ))
		
		guardar_imagen(frame2, hWnd, image);

		//SendDlgItemMessage(hWnd, PIC_VIDEOCAMERA, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	
		Mat gris2 = gris.clone();
		equalizeHist(gris, gris);
		//imshow("Escala de gris equalizado", gris);

		guardar_imagen(gris, hWnd, imageFiltrada);

		//imshow("Escala de gris", gris2);
		//detecta una tecla, si es el esc entonces fuera
		if (waitKey(16) == 27)
		{
			cout << "juimonos!!" << endl;
			break;
		}

	}
}