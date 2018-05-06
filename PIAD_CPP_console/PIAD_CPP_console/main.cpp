#include <iostream>
#include "filtros.h"
using namespace std;


void luminosidad()
{
	RGB colorMax, colorMin;
	system("cls");
	cout << "Escribe el color MAXIMO RGB: \n";
	cout << "R: "; cin >> colorMax.red;
	cout << "G: "; cin >> colorMax.green;
	cout << "B: "; cin >> colorMax.blue;
	cout << "R:[" << colorMax.red << "] G:[" << colorMax.green << "] B:[" << colorMax.blue << "]" << endl;

	cout << "Escribe el color MINIMO RGB: \n";
	cout << "R: "; cin >> colorMin.red;
	cout << "G: "; cin >> colorMin.green;
	cout << "B: "; cin >> colorMin.blue;
	cout << "R:[" << colorMin.red << "] G:[" << colorMin.green << "] B:[" << colorMin.blue << "]" << endl;

	cout << "Luminosidad: " << filtros::F_RGB::luminosidad(&colorMax, &colorMin) << endl;
	system("pause");
	
}

void promedio()
{
	RGB colorx;
	float promediox;
	system("cls");
	cout << "Escribe el color RGB: \n";
	cout << "R: "; cin >> colorx.red;
	cout << "G: "; cin >> colorx.green;
	cout << "B: "; cin >> colorx.blue;
	cout << "R:[" << colorx.red << "] G:[" << colorx.green << "] B:[" << colorx.blue << "]" << endl;
	promediox = filtros::F_RGB::promedio(&colorx);
	cout << "Promedio: " << promediox << endl;
	system("pause");
}

void luminancia()
{
	RGB colorx;
	system("cls");
	cout << "LUMINANCIA \n Escribe el color RGB: \n";
	cout << "R: "; cin >> colorx.red;
	cout << "G: "; cin >> colorx.green;
	cout << "B: "; cin >> colorx.blue;
	cout << "R:[" << colorx.red << "] G:[" << colorx.green << "] B:[" << colorx.blue << "]" << endl;
	
	cout << "Luminania: " << filtros::F_RGB::luminancia(&colorx) << endl;
	system("pause");
}

int menu = 0;
void main()
{
	do
	{
		system("cls");
		cout << "Menu, elige una opción \n";
		cout << "-1.- Salir" << endl;
		cout << "1.- Luminosidad" << endl;
		cout << "2.- Promedio" << endl;
		cout << "3.- Luminancia" << endl;
		cin >> menu;

		switch (menu)
		{
		case 1:
			luminosidad();
			break;
		case 2:
			promedio();
			break;
		case 3:
			luminancia();
			break;
		case 4:
		{
			system("cls");
			//matriz n*n
			const int matX = 3;
			const int matY = 3;
			float valorMascara = 1;
			float mascara[matX][matY];
			cout << "Tamaño de matriz: "
				<< filtros::F_MEDIA::inicializar_mascara(&(mascara[0][0]), matX, matY, valorMascara)
				<< endl;
			for (int i = 0, j; i < matY; i++)
			{
				for (j = 0; j < matX; j++) 	cout << i << "[" << mascara[i][j] << "] "; 	cout << "\n";
			}
			system("pause");
		}
			break;
		case 5:
		{
			//Media
			system("cls");
			//matriz n*n
			const int mMatX = 3;
			const int mMatY = 3;
			const int pMatX = 3;
			const int pMatY = 3;

			float mascara[mMatX][mMatY];
			float pixel[pMatX][pMatY];

			cout << "Tamaño de matriz mascara: "
				<< filtros::F_MEDIA::inicializar_mascara(&(mascara[0][0]), mMatX, mMatY, 1)
				<< endl;

			for (int i = 0, j = 0; i < mMatY; i++)
			{
				for (j = 0; j < mMatX; j++) 	cout << i << "[" << mascara[i][j] << "] "; 	cout << "\n";
			}

			cout << "Tamaño de matriz pixel: "
				<< filtros::F_MEDIA::inicializar_mascara(&(pixel[0][0]), pMatX, pMatY, 5)
				<< endl;

			for (int i = 0, j = 0; i < pMatY; i++)
			{
				for (j = 0; j < pMatX; j++) 	cout << i << "[" << pixel[i][j] << "] "; 	cout << "\n";
			}
			system("pause");
		}
			break;
		}

	} while (menu != -1);
	
}