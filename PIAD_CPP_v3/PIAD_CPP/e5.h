#pragma once
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#pragma comment(lib,"opencv_world310d.lib")

using namespace cv;
using namespace std;

//demo hecho por Rafael Rosas para los UltraLMAD
int escala = 3;

void e5(HWND hWnd, mod_picture image)
{

	cv::VideoCapture camara(0); //camara basica, si usan una muy grande
								//sera un camaron

	Mat img;					//la de trabajo

	if (!camara.isOpened())  // lo tipico de la camara
		exit(0);

	HOGDescriptor hog; //Histograma de Gradientes Orientados

	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector()); //Se carga el Support Vector Machine

	namedWindow("Detector de Racita", 1); //Creamos la ventana para despliegue

	camara.read(img); //leemos la camara para detectar la dimension de la imagen que da la camara

	Mat aux(img.rows / escala, img.cols / escala, CV_8U); //generamos dos imagenes reducidas en un tercio por lado o sea
	Mat aux2(img.rows / escala, img.cols / escala, CV_8U);//un noveno de tamaño para acelerar su proceso

	for (;;) //ciclo eterno
	{
		//leemos de nuevo la camara para entrar en accion
		camara.read(img);
		//modificamos el tamaño
		resize(img, aux, aux.size(), 0, 0, INTER_LINEAR);
		//convertimos de color a gris
		cvtColor(aux, aux2, CV_BGR2GRAY);
		//si no hay imagen adios!
		if (!img.data)
			continue;
		//generamos un arreglo de rectangulo para encuadrar a la racita
		vector<Rect> found, found_filtered;
		//le agregamos estilo para medir el tiempo de proceso, importante esta tecnica para
		//medir el desempeño
		double t = (double)getTickCount();
		//le pedimos que haga el trabajo de detectar
		hog.detectMultiScale(aux2, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
		//tiempo total de proceso
		t = (double)getTickCount() - t;
		//imprimelo, sino pa'que
		printf("tdetection time = %gms\n", t*1000. / cv::getTickFrequency());
		//contador de los ciclos para la cantidad de hallazgos
		size_t i, j;
		//comienza el ciclo
		for (i = 0; i < found.size(); i++)
		{
			//genera al primer rectangulo de los hallados
			Rect r = found[i];
			//checa si no se repiten lso rectangulos
			for (j = 0; j < found.size(); j++)
				if (j != i && (r & found[j]) == r)
					break;
			//si se acabo el arreglo lo mete al final del otro arreglo
			//este solo tendra rectangulos no repetidos
			if (j == found.size())
				found_filtered.push_back(r);
		}
		//de los hallados, a dibujar
		for (i = 0; i < found_filtered.size(); i++)
		{
			//dibuja el primero de los filtrados
			Rect r = found_filtered[i];
			//dibujemos el rectangulo un poco mas grande de lo normal
			//pa que la racita no quede mal encuadrada, el 3 es de la
			//reduccion que habiamos hecho, estamos compensando
			r.x *= escala;
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8*escala);
			r.y = r.y*escala;
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8*escala);
			rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
		}
		//lo tipico
		if (waitKey(10) >= 40)
			break;
		imshow("Detector de Racita", img);
		guardar::guardar_imagen(img, hWnd, image);
	}

}


