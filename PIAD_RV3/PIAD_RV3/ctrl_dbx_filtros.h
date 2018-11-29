#pragma once
#include <Windows.h>
#include "resource.h"
#include "OpenFileDialog.h"
#include "filtros.h"
#include "mod.picture.h"
#include "mod.filtro.h"
#include "ctrl_filtros.h"


mod_picture picNormal, picFiltrada;
mod_picture picMenu;
HWND cbx_filtros, cbx_forma, txt_mensajes, txt_path;
HWND btn_examinar, btn_recargar;
HWND btn_iniciar_camara, btn_capturar;
HWND btn_configurar_filtro, btn_aplicar_filtro;
HWND btn_guardar_normal, btn_guardar_filtrada;
HWND lbl_path, lbl_filtro;
void habilitar_todo(bool habilitar)
{
	EnableWindow(cbx_forma, true);
	EnableWindow(cbx_filtros, habilitar);
	EnableWindow(txt_mensajes, habilitar);
	EnableWindow(txt_path, habilitar);
	EnableWindow(btn_examinar, habilitar);
	EnableWindow(btn_recargar, habilitar);
	EnableWindow(btn_iniciar_camara, habilitar);
	EnableWindow(btn_capturar, habilitar);
	EnableWindow(btn_configurar_filtro, habilitar);
	EnableWindow(btn_aplicar_filtro, habilitar);
	EnableWindow(btn_guardar_normal, habilitar);
	EnableWindow(btn_guardar_filtrada, habilitar);
}
//VideoCapture camara(0);
//NOTA: AL MOMENTO DE HACER CLIC EN EL COMBOBOX ENTRA AL EVENTO INFINITAMENTE ASI QUE AL DAR CLIC EN CUALQUIERA DE LOS DOS COMBOBOX SE CICLARA CON EL ULTIMO
LRESULT CALLBACK call_filtrado(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			hWnd_dbx_filtros = hWnd;
			cbx_filtros = GetDlgItem(hWnd, CBX_FILTROS);
			cbx_forma = GetDlgItem(hWnd, CBX_ELEGIR_FORMA);
			txt_mensajes = GetDlgItem(hWnd, TXT_MENSAJES);
			txt_path = GetDlgItem(hWnd, TXT_PATH);
			btn_examinar = GetDlgItem(hWnd, BTN_EXAMINAR);
			btn_recargar = GetDlgItem(hWnd, BTN_RECARGAR);
			btn_iniciar_camara = GetDlgItem(hWnd, BTN_INICIAR_CAMARA);
			btn_capturar = GetDlgItem(hWnd, BTN_CAPTURAR);
			btn_configurar_filtro = GetDlgItem(hWnd, BTN_CONFIGURAR_FILTRO);
			btn_aplicar_filtro = GetDlgItem(hWnd, BTN_APLICAR_FILTRO);
			btn_guardar_normal = GetDlgItem(hWnd, BTN_GUARDAR_NORMAL);
			btn_guardar_filtrada = GetDlgItem(hWnd, BTN_GUARDAR_FILTRADA);
			lbl_path = GetDlgItem(hWnd, LBL_PATH);
			lbl_filtro = GetDlgItem(hWnd, LBL_FILTRO);

			objFiltro.inicializar_nombres();
			for (int i = 0; i < objFiltro.max_nomFiltro; i++)
				SendMessageA(cbx_filtros, CB_ADDSTRING, 0, (LPARAM)(objFiltro.propFiltro[i].titulo));
			for (int i = 0; i < objFiltro.max_formaFiltrado; i++)
				SendMessageA(cbx_forma, CB_ADDSTRING, 0, (LPARAM)(objFiltro.formaFiltrado[i].nombre));
			SetWindowTextA(txt_mensajes, (LPCSTR)(objFiltro.filterMSG[objFiltro.flt_ninguno].nombre));

			SendMessageA(cbx_forma, CB_SETCURSEL, 0, 0);
			SendMessageA(cbx_filtros, CB_SETCURSEL, 0, 0);

			habilitar_todo(false);
			//timer de 33 milisegs
			//SetTimer(hWnd, 100, 33, (TIMERPROC)NULL);
			SetTimer(hWnd, 100, 33, (TIMERPROC)NULL);
		

			break;
		}
		case WM_CLOSE:
		{
			dbx_filtrado.cerrar_dialogo = true;
			EndDialog(hWnd, true);
			break;
		}
		case WM_KEYUP:
		{
			switch (wParam)
			{

			}
			break;
		}
		case WM_TIMER:
		{
			char tempForma[255];
			char tempMSG[255];
			SendMessageA(cbx_forma, CB_GETLBTEXT, SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0), (LPARAM)tempForma);

			if (
				(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.reconocimiento_de_personas_desde_camara].nombre) == 0) ||
				(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.reconocimiento_de_personas_desde_imagen].nombre) == 0)
				)
			{
				char tempCHAR[255];
				char tempMSGCHAR[255];
				itoa(dbx_filtrado.personas_detectadas, tempCHAR, 10);
				strcpy_s(tempMSGCHAR, "");
				strcat_s(tempMSGCHAR, "Personas encontradas ");
				strcat_s(tempMSGCHAR, tempCHAR);
				SetWindowTextA(txt_mensajes, tempMSGCHAR);
			}
			else if (
				(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_archivo].nombre) == 0) ||
				(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_camara].nombre) == 0)
				)
			{
				if (dbx_filtrado.estado_vid_original == 1)
				{

					if ((frameClone.dims>0) && (graba != NULL))
						graba->Graba(frameClone);

				}
				else if (dbx_filtrado.estado_vid_original == 2)
				{
					if (graba != NULL && dbx_filtrado.estado_vid_original != 0)
					{
						dbx_filtrado.estado_vid_original = 0;
						graba->SalidaDeVideo.release();
						pathActivado = false;
						
						MessageBox(0, "Grabado", "grabado", 0);

					}
				}
				if (dbx_filtrado.estado_vid_filtrada == 1)
				{

					if ((frameClone2.dims>0) && (grabaF != NULL))
						grabaF->Graba(frameClone2);

				}
				else if (dbx_filtrado.estado_vid_filtrada == 2)
				{
					if (grabaF != NULL && dbx_filtrado.estado_vid_filtrada != 0)
					{
						dbx_filtrado.estado_vid_filtrada = 0;
						grabaF->SalidaDeVideo.release();
						pathActivadoF = false;
						MessageBox(0, "Grabado", "grabado", 0);

					}
				}
				
				if (dbx_filtrado.estado_vid_desde_archivo_filtrado == 1)
				{
					if ((frame_desde_archivo_filtrado.dims>0) && (graba_desde_archivo_filtrado != NULL))
						graba_desde_archivo_filtrado->Graba(frame_desde_archivo_filtrado);
				}
				else if (dbx_filtrado.estado_vid_desde_archivo_filtrado == 2)
				{
					if (graba_desde_archivo_filtrado != NULL && dbx_filtrado.estado_vid_desde_archivo_filtrado != 0)
					{
						dbx_filtrado.estado_vid_desde_archivo_filtrado = 0;
						graba_desde_archivo_filtrado->SalidaDeVideo.release();
						path_activado_desde_archivo_filtrado = false;
						MessageBox(0, "Grabado", "grabado", 0);
					}
				}
				if (dbx_filtrado.estado_vid_desde_archivo_original == 1)
				{
					if ((frame_desde_archivo_original.dims>0) && (graba_desde_archivo_original != NULL))
						graba_desde_archivo_original->Graba(frame_desde_archivo_original);
				}
				else if (dbx_filtrado.estado_vid_desde_archivo_original == 2)
				{
					if (graba_desde_archivo_original != NULL && dbx_filtrado.estado_vid_desde_archivo_original != 0)
					{
						dbx_filtrado.estado_vid_desde_archivo_original = 0;
						graba_desde_archivo_original->SalidaDeVideo.release();
						path_activado_desde_archivo_filtrado = false;
						MessageBox(0, "Grabado", "grabado", 0);
					}
				}
				time++;
			}
			
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case CBX_ELEGIR_FORMA:
				{
					for (int i = 0; i < objFiltro.max_formaFiltrado; i++)
					{
						objFiltro.formaFiltrado[i].activado = false;
					}
					//FORMA FILTRADO		
					char tempForma[255];
					char tempMSG[255];
					SendMessageA(cbx_forma, CB_GETLBTEXT, SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0), (LPARAM)tempForma);

					for (int i = 0; i < objFiltro.max_formaFiltrado; i++)
					{
						if (strcmp(tempForma, objFiltro.formaFiltrado[i].nombre) == 0)
						{
							objFiltro.formaFiltrado[i].activado = true;
							strcpy_s(tempMSG, objFiltro.filterMSG[4].nombre);
							strcat_s(tempMSG, objFiltro.formaFiltrado[i].nombre);
							SetWindowTextA(txt_mensajes, (LPCSTR)tempMSG);
						}
					}
					if (strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.ninguno].nombre)==0)
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(false);
						SetWindowTextA(lbl_path, objFiltro.recMSG[objFiltro.pathImagen].nombre);
						SetWindowTextA(lbl_filtro, objFiltro.recMSG[objFiltro.pathFiltro].nombre);
						SetWindowTextA(txt_path, "");
						
					}else if (
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_archivo].nombre) == 0) ||
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_archivo].nombre) == 0)
						)
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(false);
						EnableWindow(txt_path, true);
						
						EnableWindow(btn_examinar, true);
						
						SetWindowTextA(lbl_path, objFiltro.recMSG[objFiltro.pathImagen].nombre);
						SetWindowTextA(lbl_filtro, objFiltro.recMSG[objFiltro.pathFiltro].nombre);
						SetWindowTextA(txt_path, "");
					}else if (
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_camara].nombre) == 0) ||
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_camara].nombre) == 0) 
						)
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(false);
						EnableWindow(btn_iniciar_camara, true);
						if ((strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_camara].nombre) == 0))
						{
							EnableWindow(btn_capturar, true);
						}
						
						
						EnableWindow(cbx_filtros, true);
						SetWindowTextA(lbl_path, objFiltro.recMSG[objFiltro.pathImagen].nombre);
						SetWindowTextA(lbl_filtro, objFiltro.recMSG[objFiltro.pathFiltro].nombre);
						SetWindowTextA(txt_path, "");
					}else if ((strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.reconocimiento_de_personas_desde_camara].nombre) == 0))
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(false);
						EnableWindow(btn_iniciar_camara, true);
						
						SetWindowTextA(lbl_path, objFiltro.recMSG[objFiltro.personasReconocidas].nombre);
						SetWindowTextA(txt_path, "0");
						SetWindowTextA(lbl_filtro, objFiltro.recMSG[objFiltro.noDisponible].nombre);
					}
					else if ((strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.reconocimiento_de_personas_desde_imagen].nombre) == 0) )
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(false);
						
						EnableWindow(btn_examinar, true);
						
					}
					else if ((strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.histograma_desde_camara].nombre) == 0))
					{
						habilitar_todo(false);
						EnableWindow(btn_iniciar_camara, true);
						
					}
					else if ((strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.histograma_desde_imagen].nombre) == 0))
					{
						habilitar_todo(false);
						EnableWindow(btn_examinar, true);
					}
					break;
				}
				case CBX_FILTROS:
				{
					
					//NOMBRE FILTRADO
					for (int i = 0; i < objFiltro.max_nomFiltro; i++)
					{
						objFiltro.propFiltro[i].activado = false;
					}
					char tempFiltros[255];
					char tempMSG[255];
					SendMessageA(cbx_filtros, CB_GETLBTEXT, SendMessageA(cbx_filtros, CB_GETCURSEL, 0, 0), (LPARAM)tempFiltros);
					
					for (int i = 0; i < objFiltro.max_nomFiltro; i++)
					{
						if (strcmp(tempFiltros, objFiltro.propFiltro[i].titulo) == 0)
						{
							objFiltro.propFiltro[i].activado = true;
							strcpy_s(tempMSG, objFiltro.filterMSG[4].nombre);
							strcat_s(tempMSG, objFiltro.propFiltro[i].titulo);
							SetWindowTextA(txt_mensajes, (LPCSTR)tempMSG);
						}
				
					}
					if (objFiltro.propFiltro[0].activado)
					{
						EnableWindow(btn_configurar_filtro, false);
						EnableWindow(btn_aplicar_filtro, false);
						for (int i = 0; i < objFiltro.max_nomFiltro; i++)
							objFiltro.propFiltro[i].mantener = false;
					}
					else
					{
						
							EnableWindow(btn_configurar_filtro, true);
							EnableWindow(btn_aplicar_filtro, true);
						
					}

					break;
				}
				case BTN_INICIAR_CAMARA:
				{
					char tempFiltros[255];
					char tempMSG[255];
					SendMessageA(cbx_forma, CB_GETLBTEXT, SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0), (LPARAM)tempFiltros);

					
					//int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
					SetWindowTextA(txt_mensajes, (LPCSTR)(objFiltro.filterMSG[3].nombre));
					if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_camara].nombre)==0)
					{
						EnableWindow(btn_guardar_normal, false);
						EnableWindow(btn_guardar_filtrada, true);
						SetWindowTextA(btn_guardar_normal, objFiltro.statMSG[objFiltro.iniciar_grabado_original].nombre);
						SetWindowTextA(btn_guardar_filtrada, objFiltro.statMSG[objFiltro.iniciar_grabado_filtrado].nombre);
					}
					if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_camara].nombre)==0)
					{
						obtener_imagen_desde_camara();
					}
					else if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_camara].nombre) == 0)
					{
						obtener_video_desde_camara(objFiltro.cargar_video_desde_camara);
					}
					else if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.reconocimiento_de_personas_desde_camara].nombre) == 0)
					{
						reconocimiento_personas_desde_camara(objFiltro.reconocimiento_de_personas_desde_camara);
					}
					
					else if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.histograma_desde_camara].nombre) == 0)
					{
						mostrar_histograma_desde_camara();
					}
					
						
					break;
				}
				case BTN_CAPTURAR:
				{
					dbx_filtrado.capturar = !dbx_filtrado.capturar;
					if (dbx_filtrado.capturar)
						
						SetWindowTextA(btn_capturar, objFiltro.statMSG[objFiltro.capturar_de_nuevo].nombre);
					else
						SetWindowTextA(btn_capturar, objFiltro.statMSG[objFiltro.capturar].nombre);

					EnableWindow(btn_guardar_normal, true);
					EnableWindow(btn_guardar_filtrada, true);
					break;
				}
				
				case IDCANCEL:
				{
					EndDialog(hWnd, true);
					break;
				}
				case BTN_EXAMINAR:
				{
					char tempFiltros[255];
					char tempMSG[255];
					SendMessageA(cbx_forma, CB_GETLBTEXT, SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0), (LPARAM)tempFiltros);

				std:string path = "";
					if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_archivo].nombre) == 0)
					{
						//int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
						SetWindowTextA(txt_mensajes, (LPCSTR)(objFiltro.filterMSG[3].nombre));
						//int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
					
						path = getPathToVideo(hWnd);
						SetWindowTextA(txt_path, path.c_str());
					}
					else
					{
						//int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
						SetWindowTextA(txt_mensajes, (LPCSTR)(objFiltro.filterMSG[3].nombre));
						//int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
						path = getPathToImage(hWnd);
						SetWindowTextA(txt_path, path.c_str());
					}
					
					
					if (path != "")
					{
						EnableWindow(btn_recargar, true);
						
						if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_archivo].nombre) == 0)
						{
							EnableWindow(cbx_filtros, true);
							SetWindowTextA(txt_mensajes, (LPCSTR)objFiltro.filterMSG[0].nombre);
							EnableWindow(btn_guardar_normal, true);
							EnableWindow(btn_guardar_filtrada, true);	
							obtener_imagen_archivo(path, objFiltro.cargar_imagen_desde_archivo);
						}
						else if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_archivo].nombre) == 0)
						{	
							EnableWindow(cbx_filtros, true);
							SetWindowTextA(txt_mensajes, (LPCSTR)objFiltro.filterMSG[0].nombre);
							EnableWindow(btn_guardar_normal, true);
							EnableWindow(btn_guardar_filtrada, true);
							obtener_video_archivo(path, objFiltro.cargar_video_desde_archivo);
						}
						else if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.reconocimiento_de_personas_desde_imagen].nombre) == 0)
						{
							//EnableWindow(btn_iniciar_camara, true);
							SetWindowTextA(btn_iniciar_camara, "Comenzar reconocimiento");
							/*char tempCHAR[255];
							GetWindowText(txt_path, tempCHAR, 255);*/
							reconocimiento_personas_desde_imagen(path, objFiltro.reconocimiento_de_personas_desde_imagen);
						}
						else if (strcmp(tempFiltros, objFiltro.formaFiltrado[objFiltro.histograma_desde_imagen].nombre) == 0)
						{
							mostrar_histograma_desde_imagen(path);
						}

					}
					else
						MessageBoxA(0, "Direccion vacia", "Cargar", 0);

					
					break;
				}
				case BTN_RECARGAR:
				{
					int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
					char pathCHAR[255];
					GetWindowTextA(txt_path, pathCHAR, 255);
					//MessageBoxA(0, pathCHAR, "", 0);
					if (strcmp(pathCHAR, "") != 0)
					{
						
						if (opcion_elegida == objFiltro.cargar_imagen_desde_archivo)
						{
							SetWindowTextA(txt_mensajes, (LPCSTR)objFiltro.filterMSG[0].nombre);
							EnableWindow(btn_guardar_normal, true);
							EnableWindow(btn_guardar_filtrada, true);
							obtener_imagen_archivo(pathCHAR, objFiltro.cargar_imagen_desde_archivo);
						}
						else if (opcion_elegida == objFiltro.cargar_video_desde_archivo)
						{
							SetWindowTextA(txt_mensajes, (LPCSTR)objFiltro.filterMSG[0].nombre);
							EnableWindow(btn_guardar_normal, true);
							EnableWindow(btn_guardar_filtrada, true);
							obtener_video_archivo(pathCHAR, objFiltro.cargar_video_desde_archivo);
						}
						else if (opcion_elegida == objFiltro.reconocimiento_de_personas_desde_imagen)
						{
							reconocimiento_personas_desde_imagen(pathCHAR, objFiltro.reconocimiento_de_personas_desde_imagen);
						}
					
					}
					else
						MessageBoxA(0, "Direccion vacia", "Cargar", 0);
					break;
				}
				
				case BTN_APLICAR_FILTRO:
				{
					
					char tempFiltros[255];
					char tempMSG[255];
					SendMessageA(cbx_filtros, CB_GETLBTEXT, SendMessageA(cbx_filtros, CB_GETCURSEL, 0, 0), (LPARAM)tempFiltros);

					for (int i = 0; i < objFiltro.max_nomFiltro; i++)
					{
						if (strcmp(tempFiltros, objFiltro.propFiltro[i].titulo) == 0)
						{
							
							objFiltro.propFiltro[i].activado = true;
							strcpy_s(tempMSG, objFiltro.filterMSG[8].nombre);
							strcat_s(tempMSG, objFiltro.propFiltro[i].titulo);
							SetWindowTextA(txt_mensajes, (LPCSTR)tempMSG);
							objFiltro.propFiltro[i].mantener = true;
							char tempCHAR[255];
							strcpy_s(tempCHAR, "");
							strcat_s(tempCHAR, "Filtro ");
							strcat_s(tempCHAR, objFiltro.propFiltro[i].titulo);
							strcat_s(tempCHAR, " fijado");
							MessageBoxA(0, tempCHAR, "Filtro fijado", 0);
							
						}

					}
					
					break;
				}
				
				case BTN_GUARDAR_NORMAL:
				{
					//FORMA FILTRADO		
					char tempForma[255];
					char tempMSG[255];
					SendMessageA(cbx_forma, CB_GETLBTEXT, SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0), (LPARAM)tempForma);
					if (
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_archivo].nombre) == 0) ||
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_camara].nombre) == 0)
						)
					{
						dbx_filtrado.guardar_img_original = true;
					}
					else if (
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_archivo].nombre) == 0) ||
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_camara].nombre) == 0)
						
						)
					{
						dbx_filtrado.guardar_vid_original = !dbx_filtrado.guardar_vid_original;
						if (dbx_filtrado.guardar_vid_original)
						{
							SetWindowTextA(btn_guardar_normal, objFiltro.statMSG[objFiltro.grabando_video_original].nombre);// "Grabando...");
							dbx_filtrado.estado_vid_original = 1;
						}
						else
						{
							SetWindowTextA(btn_guardar_normal, objFiltro.statMSG[objFiltro.detener_grabado_original].nombre);//"Dejar de grabar");
							dbx_filtrado.estado_vid_original = 2;
						}
					}
						
					break;
				}
				case BTN_GUARDAR_FILTRADA:
				{	
					//FORMA FILTRADO		
					char tempForma[255];
					char tempMSG[255];
					SendMessageA(cbx_forma, CB_GETLBTEXT, SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0), (LPARAM)tempForma);
					int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
					if (
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_archivo].nombre) == 0) ||
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_camara].nombre) == 0)
						
						)
					{
						dbx_filtrado.guardar_img_filtrada = true;
					}
					else if (
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_archivo].nombre) == 0) ||
						(strcmp(tempForma, objFiltro.formaFiltrado[objFiltro.cargar_video_desde_camara].nombre) == 0)
						
						)
					{
						dbx_filtrado.guardar_vid_filtrada = !dbx_filtrado.guardar_vid_filtrada;
						if (dbx_filtrado.guardar_vid_filtrada)
						{
							SetWindowTextA(btn_guardar_filtrada, objFiltro.statMSG[objFiltro.grabando_video_filtrado].nombre);// "Grabando...");
							dbx_filtrado.estado_vid_filtrada = 1;
						}
						else
						{
							SetWindowTextA(btn_guardar_filtrada, objFiltro.statMSG[objFiltro.detener_grabado_filtrado].nombre);//"Dejar de grabar");
							dbx_filtrado.estado_vid_filtrada = 2;
						}
							

					}
					break;
				}
			}

			break;
		}
	}
	return false;
}