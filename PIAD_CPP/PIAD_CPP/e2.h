#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include <math.h>

#pragma comment(lib,"opencv_world310d.lib")


using namespace cv;
using namespace std;

void e2()
{
	Mat frame, gris, salida; //aqui guardaremos el frame
	bool exito;
	VideoCapture camara(0); //tipo de dato correspondiente a la camara


	if (!camara.isOpened())  // si no se pudo ahi muere, lastima!
	{
		cout << "No se pudo abrir la camara" << endl;
		return;
	}

	exito = camara.read(frame); // lee un frame
	if (!exito) //si no se pudo lastima de nuevo
	{
		cout << "no pude leer!" << endl;
		exit(0);
	}
	cvtColor(frame, gris, CV_BGR2GRAY, 0);
	Mat gris2 = gris.clone();
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
		subtract(gris, gris2, salida);
		gris2 = gris.clone();
		//crea la ventana y muestralo al mundo!
		imshow("Mi primer Video", frame);



		imshow("Escala de gris", gris);
		imshow("Movimiento", salida);
		//detecta una tecla, si es el esc entonces fuera
		if (waitKey(1) == 27)
		{
			cout << "juimonos!!" << endl;
			break;
		}

	}
}