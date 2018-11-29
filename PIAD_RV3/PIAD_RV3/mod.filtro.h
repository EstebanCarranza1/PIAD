#pragma once

#define E 2.71828182845904523536;
#define M_PI 3.14159265358979323846;  /* pi */

static class clsFiltro
{
public:
	/*
	strcpy_s(propFiltro[0].titulo, "<< NO SELECCIONAR NIGUNO >>");
	strcpy_s(propFiltro[1].titulo, "Efecto escala gris - Luminancia");
	strcpy_s(propFiltro[2].titulo, "Efecto escala gris - Luminosidad");
	strcpy_s(propFiltro[3].titulo, "Efecto escala gris - Promedio");
	strcpy_s(propFiltro[4].titulo, "Efecto Sepia");
	strcpy_s(propFiltro[5].titulo, "Filtro de la media");
	strcpy_s(propFiltro[6].titulo, "Filtro de la media ponderada");
	strcpy_s(propFiltro[7].titulo, "Filtro de la mediana");
	strcpy_s(propFiltro[8].titulo, "Filtro gaussiano");
	strcpy_s(propFiltro[9].titulo, "Filtro sustracción de la media");
	strcpy_s(propFiltro[10].titulo, "Filtro laplaciano");
	strcpy_s(propFiltro[11].titulo, "Filtro sobel C");*/
	static enum filtro
	{
		flt_ninguno,
		flt_luminancia,
		flt_luminosidad,
		flt_promedio,
		flt_sepia,
		flt_media,
		flt_mediaPonderada,
		flt_gaussiano,
		flt_sustraccionMedia,
		flt_laplaciano,
		flt_sobelC,
		flt_sobelF,
		flt_menosLaplaciano,
		flt_direccionNorteSur,
		flt_direccionEsteOeste,
		flt_repujado,
		flt_sharpening
	};
	static enum formaFiltrado
	{
		ninguno,
		cargar_imagen_desde_archivo,
		cargar_imagen_desde_camara,
		cargar_video_desde_archivo,
		cargar_video_desde_camara,
		reconocimiento_de_personas_desde_camara,
		reconocimiento_de_personas_desde_imagen,
		histograma_desde_camara,
		histograma_desde_imagen,
		histograma_desde_video
	};
	static enum recMSG
	{
		pathImagen,
		personasReconocidas,
		pathFiltro,
		noDisponible
	};
	static enum statMSG
	{
		vacio, 
		iniciar_grabado_original,
		iniciar_grabado_filtrado,
		detener_grabado_original,
		detener_grabado_filtrado,
		grabando,
		capturar,
		capturar_de_nuevo,
		grabando_video_original,
		grabando_video_filtrado
	};
	static const int max_nomFiltro = 17;
	static const int max_formaFiltrado = 9;
	static const int max_mensajes = 9;
	static const int max_recMSG = 4;
	static const int max_static_messages = 10;
	struct propiedades
	{
		char titulo[255];
		bool activado = false;
		bool mantener = false;
	}propFiltro[max_nomFiltro];
	struct tipoFiltrado
	{
		char nombre[255];
		bool activado = false;
	}formaFiltrado[max_formaFiltrado];
	struct mensajes
	{
		char nombre[255];
	}filterMSG[max_mensajes];
	struct mensajes_reconocimiento
	{
		char nombre[255];
	}recMSG[max_recMSG];

	struct static_messages
	{
		char nombre[255];
	}statMSG[max_static_messages];

	void inicializar_nombres()
	{
		strcpy_s(propFiltro[0].titulo, "<< NO SELECCIONAR NIGUNO >>");
		strcpy_s(propFiltro[1].titulo, "Efecto escala gris - Luminancia");
		strcpy_s(propFiltro[2].titulo, "Efecto escala gris - Luminosidad");
		strcpy_s(propFiltro[3].titulo, "Efecto escala gris - Promedio");
		strcpy_s(propFiltro[4].titulo, "Efecto Sepia");
		strcpy_s(propFiltro[5].titulo, "Filtro de la media");
		strcpy_s(propFiltro[6].titulo, "Filtro de la media ponderada");
		strcpy_s(propFiltro[7].titulo, "Filtro gaussiano");
		strcpy_s(propFiltro[8].titulo, "Filtro sustracción de la media");
		strcpy_s(propFiltro[9].titulo, "Filtro laplaciano");
		strcpy_s(propFiltro[10].titulo, "Filtro sobel C");
		strcpy_s(propFiltro[11].titulo, "Filtro sobel F");
		strcpy_s(propFiltro[12].titulo, "Menos laplaciano");
		strcpy_s(propFiltro[13].titulo, "Direccion Norte Sur");
		strcpy_s(propFiltro[14].titulo, "Direccion Este Oeste");
		strcpy_s(propFiltro[15].titulo, "Repujado");
		strcpy_s(propFiltro[16].titulo, "Sharpening");
		
		
		strcpy_s(formaFiltrado[0].nombre, "<< NO SELECCIONAR NINGUNO >>");
		strcpy_s(formaFiltrado[1].nombre, "Filtro - Cargar imagen desde archivo");
		strcpy_s(formaFiltrado[2].nombre, "Filtro - Cargar imagen desde camara");
		strcpy_s(formaFiltrado[3].nombre, "Filtro - Cargar video desde archivo");
		strcpy_s(formaFiltrado[4].nombre, "Filtro - Video desde camara");
		strcpy_s(formaFiltrado[5].nombre, "Reconocimiento de personas desde camara");
		strcpy_s(formaFiltrado[6].nombre, "Reconocimiento de personas desde imagen");
		strcpy_s(formaFiltrado[7].nombre, "Mostrar histograma desde camara");
		strcpy_s(formaFiltrado[8].nombre, "Mostrar histograma desde imagen");
		//strcpy_s(formaFiltrado[9].nombre, "Mostrar histograma desde video");

		strcpy_s(filterMSG[0].nombre, "<< NO SELECCIONAR NINGUNO >>");
		strcpy_s(filterMSG[1].nombre, "ABRE LA CÁMARA PARA COMENZAR");
		strcpy_s(filterMSG[2].nombre, "ELIGE UNA FORMA DE FILTRADO");
		strcpy_s(filterMSG[3].nombre, "ELIGE UN FILTRO/EFECTO");
		strcpy_s(filterMSG[4].nombre, "");// "HAS SELECCIONADO: ");
		strcpy_s(filterMSG[5].nombre, "CAMARA INICIADA - ELIGE UNA FORMA DE FILTRADO");
		strcpy_s(filterMSG[6].nombre, "IMAGEN CARGADA CON EXITO");
		strcpy_s(filterMSG[7].nombre, "CARGADANDO IMAGEN");
		strcpy_s(filterMSG[8].nombre, "SE FIJO ");


		strcpy_s(recMSG[0].nombre, "Direccion de la imagen: ");
		strcpy_s(recMSG[1].nombre, "Personas reconocidas: ");
		strcpy_s(recMSG[2].nombre, "Filtro: ");
		strcpy_s(recMSG[3].nombre, "N/D");

		strcpy_s(statMSG[0].nombre, "");
		strcpy_s(statMSG[1].nombre, "Iniciar grabado original");
		strcpy_s(statMSG[2].nombre, "Iniciar grabado filtrado");
		strcpy_s(statMSG[3].nombre, "Guardando original");
		strcpy_s(statMSG[4].nombre, "Guardando filtrado");
		strcpy_s(statMSG[5].nombre, "Grabando..");
		strcpy_s(statMSG[6].nombre, "Capturar");
		strcpy_s(statMSG[7].nombre, "Capturar de nuevo");
		strcpy_s(statMSG[8].nombre, "Grabando original..");
		strcpy_s(statMSG[9].nombre, "Grabando filtrado..");
		


	}
	class matrices
	{
		public:
		int gaussiano[9] =
		{
			1,5,1,
			5,35,5,
			1,5,1

		};
		int media[9] =
		{
			1, 1, 1,
			1, 1, 1,
			1, 1, 1
		};
		int mediaPonderada[9] =
		{
			1, 1, 1,
			1, 3, 1,
			1, 1, 1
		};
		int sustraccionMedia[9] =
		{
			-1, -1, -1,
			-1, 8, -1,
			-1, -1, -1
		};
		int laplaciano[9] =
		{
			0, 1, 0,
			1, -4, 1,
			0, 1, 0
		};
		int menosLaplaciano[9] = 
		{
			0, -1, 0, 
			-1, 5, -1,
			0, -1, 0
		};
		int direccionNorteSur[9] =
		{
			1, 1, 1,
			1, -2, 1,
			-1, -1, -1
		};
		int direccionEsteOeste[9] =
		{
			-1, 1, 1,
			-1, 2, 1,
			-1, 1, 1
		};
		int sobelC[9] =
		{
			-1, 0, 1,
			-2, 0, 2,
			-1, 0, 1
		};
		int sobelF[9] =
		{
			-1, -2, -1,
			0, 0, 0,
			1, 2, 1
		};
		int repujado[9] =
		{
			-2, 1, 0,
			-1, 1, 1,
			0, 1, 2
		};
		int sharpening[9] =
		{
			-1,-1,-1,
			-1,9,-1,
			-1,-1,-1
			/*1,0,-1,
			2,0,-2,
			1,0,-1
			/*0,0,1,
			0,1,0,
			1,0,0*/
		};

		void elevarPonderacionMedia(int ponderacion)
		{
			mediaPonderada[4] = ponderacion;
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
		
	}matrices;
}objFiltro;



