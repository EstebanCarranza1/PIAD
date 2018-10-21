#pragma once



static class clsFiltro
{
public:
	static const int max_nomFiltro = 13;
	static const int max_formaFiltrado = 5;
	static const int max_mensajes = 10;
	struct propiedades
	{
		char titulo[255];
		bool activado = false;	
	}propFiltro[max_nomFiltro];
	struct tipoFiltrado
	{
		char nombre[255];
		bool activado = false;
	}formaFiltrado[max_formaFiltrado];
	struct mensajes
	{
		char nombre[255];
	}filterMSG[3];

	void inicializar_nombres()
	{
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
		strcpy_s(propFiltro[11].titulo, "Filtro sobel C");
		strcpy_s(propFiltro[12].titulo, "Filtro sobel F");

		strcpy_s(formaFiltrado[0].nombre, "<< NO SELECCIONAR NINGUNO >>");
		strcpy_s(formaFiltrado[1].nombre, "Cargar imagen desde archivo");
		strcpy_s(formaFiltrado[2].nombre, "Cargar imagen desde camara");
		strcpy_s(formaFiltrado[3].nombre,  "Cargar video desde archivo");
		strcpy_s(formaFiltrado[4].nombre,  "Cargar video desde camara");
		
		strcpy_s(filterMSG[0].nombre, "<< NO SELECCIONAR NINGUNO >>");
		strcpy_s(filterMSG[1].nombre, "ABRE LA CÁMARA PARA COMENZAR");
		strcpy_s(filterMSG[2].nombre, "ELIGE UNA FORMA DE FILTRADO");
		strcpy_s(filterMSG[3].nombre, "ELIGE UN FILTRO/EFECTO");
		strcpy_s(filterMSG[4].nombre, "HAS SELECCIONADO: ");
		strcpy_s(filterMSG[5].nombre, "CAMARA INICIADA - ELIGE UNA FORMA DE FILTRADO");
		strcpy_s(filterMSG[6].nombre, "IMAGEN CARGADA CON EXITO");


	}
}objFiltro;



