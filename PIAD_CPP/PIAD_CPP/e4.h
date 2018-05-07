#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <conio.h>
#include <iostream>

#pragma comment(lib,"opencv_world310d.lib")

using namespace std;
using namespace cv;

//prototipo de la funcion de captura cara y ojos
void CaraYOjos(Mat frame, float escala);

//definicion de los haarcascades
String face_cascade_name = "haarcascade\\haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade\\haarcascade_eye.xml";

//contenedores de los haarcascades
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

//nombre de la ventana
string window_name = "Captura y deteccion de cara";

void e4()
{
	//Inicializamos la ventana
	VideoCapture captura(0);

	//matriz de pixels donde se depositara lo que viene de la camara
	Mat frame;

	//cargamos los haarcascades a los contenedores
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading\n"); exit(0); };
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)Error loading\n"); exit(0); };

	//checamos si la camara esta activa
	if (!captura.isOpened())
		exit(0);

	//lazo infinito de deteccion
	while (true)
	{
		//leemos un frame
		if (!captura.read(frame))
			break;

		Mat frame2(frame, Rect(200, 100, 240, 240));
		//en caso de que se haya leido sin error se procesa con la funcion de cara y ojos
		if (!frame2.empty())
		{
			CaraYOjos(frame2, 1);
		}
		else
		{
			printf("sin informacion");
			break;
		}

		int c = waitKey(10);
		if ((char)c == 'c')
		{
			break;
		}
	}
}


void CaraYOjos(Mat frame, float escala)
{
	//arreglo de rectangulos de caras detectadas
	std::vector<Rect> faces;

	//nuevo frame se utilizara para la conversion a gris
	Mat frame_gray;

	//creamos una matriz de pixeles menor segun la escala
	//para procesar mas rapido
	Mat nuevo(cvRound(frame.rows / escala), cvRound(frame.cols / escala), CV_8UC1);
	//aqui convertimos a escala de gris
	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	//aqui generamos un cuadro menor de tamaño con filtro lineal
	resize(frame_gray, nuevo, nuevo.size(), 0, 0, INTER_LINEAR);
	//acentuamos los contrastes con equalizacion de historgrama
	equalizeHist(nuevo, nuevo);

	//este contenedor con el metodo detectMultiScale busca en la imagen y entrega un arreglo de rectangulos
	//donde cada uno encierra una cara
	face_cascade.detectMultiScale(nuevo, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	//le damos una recorrida a cada rectangulo y aprovechamos sus datos para generar circunferencias 
	//una para cada cara
	for (int i = 0; i < faces.size(); i++)
	{
		//definimos el centro y compensamos con la escala
		Point center((faces[i].x + faces[i].width*0.5)*escala, (faces[i].y + faces[i].height*0.5)*escala);
		ellipse(frame, center, Size(faces[i].width*0.5*escala, faces[i].height*0.5*escala), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

		//el ROI es area de interes, es decir reducimos el area de busqueda para acelerar la deteccion, en este caso
		//el ROI es la cara y solo ahi buscamos ojos
		Mat faceROI = nuevo(faces[i]);
		//creamos un arreglo de ojos por cara 
		std::vector<Rect> eyes;
		//busca los ojos en la cara segun su haarcascade
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		//de los ojos detectados creara un circulo por cada uno
		for (int j = 0; j < eyes.size(); j++)
		{
			Point center((faces[i].x + eyes[j].x + eyes[j].width*0.5)*escala, (faces[i].y + eyes[j].y + eyes[j].height*0.5)*escala);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25 *escala);
			circle(frame, center, radius, Scalar(255, 0, 0), 4, 8, 0);
		}
	}
	//muestra lo que resulta
	imshow(window_name, frame);
}