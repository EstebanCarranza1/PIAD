#pragma once
#include "ctrl_multimedia.h"
static class ctrl_filtros
{
	public:
		static class modes
		{
			public:
			static void imagen_desde_archivo(char path[255])
			{
				Mat frame = mod_multimedia::imagen::LoadOfPC(path);
				Mat frame_filtrado = frame.clone();
				if (frame.empty())                      // Check for invalid input
				{
					MessageBoxA(0, "Could not open or find the image", "", 0);
				}
				int channels = frame.channels();
				int nRows = frame.rows;
				//las columnas efectivas de la imagen
				int nCols = frame.cols * channels;

				//Mat frameX(frame, Rect(0, 0, 640, 480));
				

				int i, j, k = 0;
				//punteros para manejar a la imagen
				uchar *p, *q;
				for (i = 0; i < nRows; i++)
				{
					p = frame.ptr<uchar>(i);
					q = frame_filtrado.ptr<uchar>(i);

					for (j = 0; j < nCols; j += 3)
					{
						//b
						q[j] = (p[j] * 0.11) + (p[j + 1] * 0.59) + (p[j + 2] * 0.30);
						//g
						q[j + 1] = (p[j] * 0.11) + (p[j + 1] * 0.59) + (p[j + 2] * 0.30);
						//r		   
						q[j + 2] = (p[j] * 0.11) + (p[j + 1] * 0.59) + (p[j + 2] * 0.30);
						/*copia(p, q, j);
						luminancia(p, q, j,true);
						luminosidad(p, q, j, nCols, objFiltro.propFiltro[2].activado);
						promedio(p, q, j, objFiltro.propFiltro[3].activado);
						sepia(p, q, j, objFiltro.propFiltro[4].activado);*/
					}
				}
				imshow("Imagen sin filtrar", frame);
				imshow("Imagen filtrada", frame_filtrado);
				if (waitKey(16) == 27)
				{
					cout << "juimonos!!" << endl;
				}
			}
		};
	
};