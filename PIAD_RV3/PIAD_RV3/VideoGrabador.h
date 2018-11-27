//Clase hecha por el Profesor Rafael Rosas
//para los hyperpawas de LMAD
//Graba video, deben de bajar el Codec XVID
//el oopencv solo genera avi como formato de contenedor

#ifndef videograbador
#define videograbador

#include <opencv2/highgui/highgui.hpp>
using namespace cv;

class VideoGrabador
{
public:
	int camara;
	VideoWriter SalidaDeVideo;
	int codec;
	int ancho;
	int alto;
	int fps;

	VideoGrabador(int Camara, char* nombre, int Codec, int Ancho, int Alto, int FPS)
	{
		camara = Camara;
		bool estado = SalidaDeVideo.open(nombre, CV_FOURCC('X', 'V', 'I', 'D'), FPS, Size(Ancho, Alto),true );
		codec = Codec;
		ancho = Ancho;
		alto = Alto;
	}

public:
	void Graba(Mat cuadro)
	{
		SalidaDeVideo.write(cuadro);
	}

	//en sus pruebas es muy importante que cierren su aplicacion
	//con la x de la esquina superior derecha de su ventana de windows api
	//ya que si la cierran con el cuadrito rojo del IDE no se ejecuta el 
	//destructor y no se cierra correctamente el video dando error en la 
	//reproduccion
	~VideoGrabador()
	{
		SalidaDeVideo.release();
	}
};

#endif