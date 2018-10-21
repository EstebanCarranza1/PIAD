#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <math.h>

#pragma comment(lib,"opencv_world310.lib")


using namespace cv;
using namespace std;

void e3()
{
	Mat frame, gris, blureado; //aqui guardaremos el frame
	VideoCapture camara(0); //tipo de dato correspondiente a la camara


	if (!camara.isOpened())  // si no se pudo ahi muere, lastima!
	{
		cout << "No se pudo abrir la camara" << endl;
		return;
	}
	//ciclo infinito para la lectura de la camara
	while (1)
	{

		bool exito = camara.read(frame); // lee un frame
		if (!exito) //si no se pudo lastima de nuevo
		{
			cout << "no pude leer!" << endl;
			break;
		}
		cvtColor(frame, gris, CV_BGR2GRAY, 0);
		blur(gris, blureado, Size(7, 7), Point(-1, -1), 4);
		//crea la ventana y muestralo al mundo!
		imshow("Mi primer Video", frame);
		imshow("Blureado", blureado);
		imshow("Escala de gris", gris);
		//detecta una tecla, si es el esc entonces fuera
		if (waitKey(16) == 27)
		{
			cout << "juimonos!!" << endl;
			break;
		}

	}
}