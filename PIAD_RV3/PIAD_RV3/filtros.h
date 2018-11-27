#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <iostream>
#include <ctype.h>
#include "resource.h"
#include <math.h>
#include "convert.h"
#include "dbx_filtros.h"
#include "mod.picture.h"
#include "mod.filtro.h"
#include "ctrl_multimedia.h"
#include "mod.saveData.h"
#define E 2.71828182845904523536;
# define M_PI 3.14159265358979323846;  /* pi */


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


void calculate_sigma(float sigma, int filter[])
{
	//float sigma = 0.75;
	float operation1 = -1 * ((pow(-1, 2) + pow(-1, 2)) / pow(sigma, 2));
	float operation2 = -1 * ((pow(-1, 2) + pow(0, 2)) / pow(sigma, 2));
	float operation3 = -1 * ((pow(0, 2) + pow(0, 2)) / pow(sigma, 2));
	float e = E;
	float pi = M_PI;
	float operation1_1 = ((2 * pi)*(pow(sigma, 2)));
	float result1 = ((pow(e, operation1) != 0) ? (pow(e, operation1)) : 1) / operation1_1;
	float result2 = ((pow(e, operation2) != 0) ? (pow(e, operation2)) : 1) / operation1_1;
	float result3 = ((pow(e, operation3) != 0) ? (pow(e, operation3)) : 1) / operation1_1;
	float min = 0;
	
	(result1 > 255) ? result1 = 255.0 : result1 = result1;
	(result1 < 0) ? result1 = 0.0 : result1 = result1;
	(result2 > 255) ? result2 = 255.0 : result1 = result2;
	(result2 < 0) ? result2 = 0.0 : result2 = result2;
	(result3> 255) ? result3 = 255.0 : result1 = result3;
	(result3 < 0) ? result3 = 0.0 : result3 = result3;

	if (result1 < result2 && result1 < result3)			min = result1;
	else if (result2 < result1 && result2 < result3)	min = result2;
	else if (result3 < result1 && result3 < result2)	min = result3;
	result1 = result1 / min;
	result2 = result2 / min;
	result3 = result3 / min;

	filter[0] = result1; filter[1] = result2; filter[2] = result1;
	filter[3] = result2; filter[4] = result3; filter[5] = result2;
	filter[6] = result1; filter[7] = result2; filter[8] = result1;
}
void insertionSort(int window[])
{
	int temp, i, j;
	for (i = 0; i < 9; i++) {
		temp = window[i];
		for (j = i - 1; j >= 0 && temp < window[j]; j--) {
			window[j + 1] = window[j];
		}
		window[j + 1] = temp;
	}
}
int FloorPixel(int i)
{
	if (i >= 255) { i = 255; }
	else if (i <= 0) { i = 0; }
	return i;
}

void aplicar_matriz_a_imagen( Mat *principal, int matriz_filtro[])
{
	
		Mat matClone = principal->clone();
		int matriz_filtroRadius = sqrt(sizeof(matriz_filtro) + 1);
		int matriz_filtroCenter = (matriz_filtroRadius / 2) + 1;
		int DIV = 0;

		// Generar DIV
		for (int i = 0; i <= sizeof(matriz_filtro); i++)
		{
			DIV += matriz_filtro[i];
		}

		if (DIV <= 0) { DIV = 1; }

		int columns = matClone.cols * matClone.channels();
		for (int matRow = 1; matRow < matClone.rows - 1; matRow++)
		{
			uchar *filaPrincipal = principal->ptr<uchar>(matRow);
			for (int matColumn = 3; matColumn < columns - 3; matColumn += 3)
			{
				int Red = 0, Blue = 0, Green = 0;

				// Procesar matriz_filtro
				for (int matriz_filtroRow = 0; matriz_filtroRow < matriz_filtroRadius; matriz_filtroRow++)
				{
					int row = matRow + (matriz_filtroRow - (matriz_filtroCenter - 1));
					uchar *clonarFila = matClone.ptr<uchar>(row);

					for (int matriz_filtroColumn = 0; matriz_filtroColumn < matriz_filtroRadius; matriz_filtroColumn++)
					{
						int column = matColumn + ((matriz_filtroColumn - (matriz_filtroCenter - 1)) * 3);

						int indexmatriz_filtro = (matriz_filtroRow * matriz_filtroRadius) + matriz_filtroColumn;
						int currentCellmatriz_filtro = matriz_filtro[indexmatriz_filtro];

						Blue += (clonarFila[column] * currentCellmatriz_filtro);
						Green += (clonarFila[column + 1] * currentCellmatriz_filtro);
						Red += (clonarFila[column + 2] * currentCellmatriz_filtro);
					}
				}

				Blue = Blue / DIV;
				Green = Green / DIV;
				Red = Red / DIV;

				filaPrincipal[matColumn] = FloorPixel(Blue);
				filaPrincipal[matColumn + 1] = FloorPixel(Green);
				filaPrincipal[matColumn + 2] = FloorPixel(Red);
			}
		}
	
	
}
void gausiano( bool activar, Mat *frame2)
{
	if (activar) {
		//objFiltro.matrices.calculate_sigma(0.75, objFiltro.matrices.gaussiano);
		aplicar_matriz_a_imagen(frame2, objFiltro.matrices.gaussiano);

	}
}
void sustraccionMedia(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.sustraccionMedia);
}
void media(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.media);
}
void mediaPonderada(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.mediaPonderada);
}
void laplaciano(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.laplaciano);
}
void menosLaplaciano(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.menosLaplaciano);
}
void direccionNorteSur(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.direccionNorteSur);
}
void direccionEsteOeste(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.direccionEsteOeste);
}
void sobelC(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.sobelC);
}
void sobelF(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.sobelF);
}
void repujado(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.repujado);
}
void sharpening(bool activar, Mat *frame2)
{
	if (activar) aplicar_matriz_a_imagen(frame2, objFiltro.matrices.sharpening);
}
void mat()
{
	dbx_filtrado.cerrar_dialogo = false;
	bool iniciar_filtrado = true;
	Mat dst; Mat src;
	// Load an image
	src = imread("C:\\DATA\\original.png", CV_LOAD_IMAGE_GRAYSCALE);
	//create a sliding window of size 9
	int window[9];

	dst = src.clone();
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			dst.at<uchar>(y, x) = 0.0;

	dbx_filtrado.cerrar_dialogo = false;

	while (iniciar_filtrado)
	{
	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {

			// Pick up window element

			window[0] = src.at<uchar>(y - 1, x - 1);
			window[1] = src.at<uchar>(y, x - 1);
			window[2] = src.at<uchar>(y + 1, x - 1);
			window[3] = src.at<uchar>(y - 1, x);
			window[4] = src.at<uchar>(y, x);
			window[5] = src.at<uchar>(y + 1, x);
			window[6] = src.at<uchar>(y - 1, x + 1);
			window[7] = src.at<uchar>(y, x + 1);
			window[8] = src.at<uchar>(y + 1, x + 1);

			// sort the window to find median
			insertionSort(window);

			// assign the median to centered element of the matrix
			dst.at<uchar>(y, x) = window[4];
		}
	}

	namedWindow("final");
	imshow("final", dst);

	namedWindow("initial");
	imshow("initial", src);


		if (waitKey(16) == 27 || dbx_filtrado.cerrar_dialogo)
		{
			cvDestroyWindow("final");
			cvDestroyWindow("initial");
			break;
		}
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
	int chanelsRGB = 3;
	for (i = 0; i < nRows; i++)
	{
		p = frame.ptr<uchar>(i);
		q = frame2.ptr<uchar>(i);
		for (j = 0; j < nCols; j += chanelsRGB)
		{
			copia(p, q, j);
			luminancia(p, q, j, objFiltro.propFiltro[objFiltro.flt_luminancia].activado);
			luminosidad(p, q, j, nCols, objFiltro.propFiltro[objFiltro.flt_luminosidad].activado);
			promedio(p, q, j, objFiltro.propFiltro[objFiltro.flt_promedio].activado);
			sepia(p, q, j, objFiltro.propFiltro[objFiltro.flt_sepia].activado);
		}
	}
	media(objFiltro.propFiltro[objFiltro.flt_media].activado, &frame2);
	mediaPonderada(objFiltro.propFiltro[objFiltro.flt_mediaPonderada].activado, &frame2);
	gausiano( objFiltro.propFiltro[objFiltro.flt_gaussiano].activado, &frame2);
	sustraccionMedia(objFiltro.propFiltro[objFiltro.flt_sustraccionMedia].activado, &frame2);
	laplaciano(objFiltro.propFiltro[objFiltro.flt_laplaciano].activado, &frame2);
	menosLaplaciano(objFiltro.propFiltro[objFiltro.flt_menosLaplaciano].activado, &frame2);
	direccionNorteSur(objFiltro.propFiltro[objFiltro.flt_direccionNorteSur].activado, &frame2);
	direccionEsteOeste(objFiltro.propFiltro[objFiltro.flt_direccionEsteOeste].activado, &frame2);
	sobelC(objFiltro.propFiltro[objFiltro.flt_sobelC].activado, &frame2);
	sobelF(objFiltro.propFiltro[objFiltro.flt_sobelF].activado, &frame2);
	repujado(objFiltro.propFiltro[objFiltro.flt_repujado].activado, &frame2);
	sharpening(objFiltro.propFiltro[objFiltro.flt_sharpening].activado, &frame2);

	if (frame.dims > 0 && frame2.dims > 0)
	{
		imshow("Imagen sin filtrar", frame);
		if (formaFiltrado != objFiltro.reconocimiento_de_personas)
			imshow("Imagen filtrada", frame2);
	}
	else dbx_filtrado.cerrar_dialogo = true;
				
	if (objFiltro.cargar_imagen_desde_archivo || objFiltro.cargar_imagen_desde_camara)
	{
		if (dbx_filtrado.guardar_img_original)
		{
			dbx_filtrado.guardar_img_original = false;
			std::string path = getPathToSaveImage(0);
			if (path != "")
			{
				if (mod_multimedia::imagen::SaveOfPC(frame, path) == 0)	MessageBoxA(0, "La imagen original fue guardada con exito", "Guardar imagen", 0);
				else MessageBoxA(0, "Hubo un error al guardar", "Guardar imagen", 0);
			}
			else MessageBoxA(0, "Elegir donde quiere guardar la imagen", "Guardar imagen", 0);
		}
		else if (dbx_filtrado.guardar_img_filtrada)
		{
			dbx_filtrado.guardar_img_filtrada = false;
			std::string path = getPathToSaveImage(0);
			if (path != "")
			{
				if (mod_multimedia::imagen::SaveOfPC(frame2, path) == 0) MessageBoxA(0, "La imagen original fue guardada con exito", "Guardar imagen", 0);
				else MessageBoxA(0, "Hubo un error al guardar", "Guardar imagen", 0);
			}
			else MessageBoxA(0, "Elegir donde quiere guardar la imagen", "Guardar imagen", 0);
		}
	}
}

void obtener_imagen_archivo(std::string path, int formaFiltrado)
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
		frame2 = frame.clone();
		dbx_filtrado.cerrar_dialogo = false;
		//calculate_sigma(0.75, matSigma);
		while (true)
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
	else
	{
		dbx_filtrado.cerrar_dialogo = true;
		MessageBoxA(0, "Esta imagen no se puede cargar correctamente, verifique que la dirección o el nombre de la imagen no sean muy largos y/o que estén guardadas con el formato apropiado", "Carga de imagen", 0);
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
void obtener_video_archivo(std::string path, int formaFiltrado)
{
	dbx_filtrado.cerrar_dialogo = false;
	CvCapture* capture = NULL;
	capture = cvCreateFileCapture(path.c_str());
	IplImage* frameVid = NULL;
	Mat frame, frame2;
	Mat resize;
	while (1)
	{
		frameVid = cvQueryFrame(capture);
		if (!frameVid) break;
		frame = cv::cvarrToMat(frameVid);
		cv::resize(frame, resize, Size(640, 480), 0, 0, INTER_CUBIC);
		frame = NULL;
		frame = resize.clone();
		//iniciar_filtrado = true;
		frame2 = frame.clone();
		filtrar(frame, frame2, objFiltro.cargar_video_desde_archivo);
		if (waitKey(16) == 27 || dbx_filtrado.cerrar_dialogo)
		{
			cvDestroyWindow("Imagen sin filtrar");
			cvDestroyWindow("Imagen filtrada");
			break;
		}
	}
}
void obtener_video_desde_camara(int formaFiltrado)
{

}
int escala = 3;
void reconocimiento_personas(int formaFiltrado)
{
	dbx_filtrado.cerrar_dialogo = false;
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
		if (waitKey(10) >= 40 || dbx_filtrado.cerrar_dialogo)
		{ 
			cvDestroyWindow("Detector de Racita");
			break;
		}
			
		imshow("Detector de Racita", img);
	}
}
