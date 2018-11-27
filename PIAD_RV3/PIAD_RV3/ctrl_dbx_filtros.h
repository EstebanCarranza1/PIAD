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
			if (dbx_filtrado.estado_vid_original == 4)
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
					MessageBox(0, "Grabado", "grabado", 0);
					
				}
			}
			//time++;
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
					if (objFiltro.formaFiltrado[objFiltro.ninguno].activado)
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(false);
						SetWindowTextA(lbl_path, objFiltro.recMSG[objFiltro.pathImagen].nombre);
						SetWindowTextA(lbl_filtro, objFiltro.recMSG[objFiltro.pathFiltro].nombre);
						SetWindowTextA(txt_path, "");
						
					}else if (objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_archivo].activado || 
						objFiltro.formaFiltrado[objFiltro.cargar_video_desde_archivo].activado)
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(false);
						EnableWindow(txt_path, true);
						EnableWindow(btn_recargar, true);
						EnableWindow(btn_examinar, true);
						EnableWindow(cbx_filtros, true);
						SetWindowTextA(lbl_path, objFiltro.recMSG[objFiltro.pathImagen].nombre);
						SetWindowTextA(lbl_filtro, objFiltro.recMSG[objFiltro.pathFiltro].nombre);
						SetWindowTextA(txt_path, "");
					}else if (objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_camara].activado || 
						objFiltro.formaFiltrado[objFiltro.cargar_video_desde_camara].activado)
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(true);
						EnableWindow(btn_iniciar_camara, true);
						if(objFiltro.formaFiltrado[objFiltro.cargar_imagen_desde_camara].activado)
							EnableWindow(btn_capturar, true);
						
						EnableWindow(cbx_filtros, true);
						SetWindowTextA(lbl_path, objFiltro.recMSG[objFiltro.pathImagen].nombre);
						SetWindowTextA(lbl_filtro, objFiltro.recMSG[objFiltro.pathFiltro].nombre);
						SetWindowTextA(txt_path, "");
					}else if (objFiltro.formaFiltrado[objFiltro.reconocimiento_de_personas].activado)
					{
						dbx_filtrado.cerrar_dialogo = true;
						habilitar_todo(false);
						EnableWindow(btn_iniciar_camara, true);
						
						SetWindowTextA(lbl_path, objFiltro.recMSG[objFiltro.personasReconocidas].nombre);
						SetWindowTextA(txt_path, "0");
						SetWindowTextA(lbl_filtro, objFiltro.recMSG[objFiltro.noDisponible].nombre);
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
					int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
					SetWindowTextA(txt_mensajes, (LPCSTR)(objFiltro.filterMSG[3].nombre));
					if (objFiltro.formaFiltrado[objFiltro.cargar_video_desde_camara].activado)
					{
						EnableWindow(btn_guardar_normal, true);
						EnableWindow(btn_guardar_filtrada, true);
						SetWindowTextA(btn_guardar_normal, objFiltro.statMSG[objFiltro.iniciar_grabado_original].nombre);
						SetWindowTextA(btn_guardar_filtrada, objFiltro.statMSG[objFiltro.iniciar_grabado_filtrado].nombre);
					}
					if (opcion_elegida == objFiltro.cargar_imagen_desde_camara)
					{
						obtener_imagen_desde_camara();
					}
					else if (opcion_elegida == objFiltro.cargar_video_desde_camara)
					{
						obtener_video_desde_camara(objFiltro.cargar_video_desde_camara);
					}
					else if (opcion_elegida == objFiltro.reconocimiento_de_personas)
					{
						reconocimiento_personas(objFiltro.reconocimiento_de_personas);
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
					//char pathCHAR[255];
					int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
					//LPCWSTR path = NULL;
					//LPCSTR str;// = existingstr.c_str();
					std:string path = "";
					if (opcion_elegida == objFiltro.cargar_imagen_desde_archivo) //objFiltro.cargar_imagen_desde_camara)
					{
						 path = getPathToImage(hWnd);
						 //strcpy_s(pathCHAR, convertLPCWSTRtoCHAR(path));
						 //SetWindowTextA(txt_path, pathCHAR);
						 SetWindowTextA(txt_path, path.c_str());
						// MessageBoxA(0, path.c_str(), "", 0);
					}else if (opcion_elegida == objFiltro.cargar_video_desde_archivo)
					{
						path = getPathToVideo(hWnd);
						SetWindowTextA(txt_path, path.c_str());
					}
					
					if (path != "")
					{
						SetWindowTextA(txt_mensajes, (LPCSTR)objFiltro.filterMSG[0].nombre);
						EnableWindow(btn_guardar_normal, true);
						EnableWindow(btn_guardar_filtrada, true);	
						if (opcion_elegida == objFiltro.cargar_imagen_desde_archivo)
						{
							obtener_imagen_archivo(path, objFiltro.cargar_imagen_desde_archivo);
						}
						else if (opcion_elegida == objFiltro.cargar_video_desde_archivo)
						{	
							obtener_video_archivo(path, objFiltro.cargar_video_desde_archivo);
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
						SetWindowTextA(txt_mensajes, (LPCSTR)objFiltro.filterMSG[0].nombre);
						EnableWindow(btn_guardar_normal, true);
						EnableWindow(btn_guardar_filtrada, true);


						if (opcion_elegida == objFiltro.cargar_imagen_desde_archivo)
						{
							obtener_imagen_archivo(pathCHAR, objFiltro.cargar_imagen_desde_archivo);
						}
						else if (opcion_elegida == objFiltro.cargar_video_desde_archivo)
						{
							obtener_video_archivo(pathCHAR, objFiltro.cargar_video_desde_archivo);
						}
					}
					else
						MessageBoxA(0, "Direccion vacia", "Cargar", 0);
					break;
				}
				
				case BTN_APLICAR_FILTRO:
				{
					
					//calculate_sigma(0.1, matSigma);
					//int c = 0;
					//mat();
					//DialogBox(dbx_menu.hInst, MAKEINTRESOURCE(DBX_CONSOLE), NULL, reinterpret_cast<DLGPROC>(call_console));
					//lbx_console = GetDlgItem(hWnd_dbx_console, LBX_CONSOLE);
					//SendMessageA(lbx_console, LB_INSERTSTRING, 0, (LPARAM)"ctrl_dbx_filtros");
					break;
				}
				
				case BTN_GUARDAR_NORMAL:
				{
					int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
					if (
						opcion_elegida == objFiltro.cargar_imagen_desde_archivo ||
						opcion_elegida == objFiltro.cargar_imagen_desde_camara
						)
					{
						dbx_filtrado.guardar_img_original = true;
					}
					else if (
						opcion_elegida == objFiltro.cargar_video_desde_archivo ||
						opcion_elegida == objFiltro.cargar_video_desde_camara
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
					int opcion_elegida = SendMessageA(cbx_forma, CB_GETCURSEL, 0, 0);
					if (
						opcion_elegida == objFiltro.cargar_imagen_desde_archivo ||
						opcion_elegida == objFiltro.cargar_imagen_desde_camara
						)
					{
						dbx_filtrado.guardar_img_filtrada = true;
					}
					else if (
						opcion_elegida == objFiltro.cargar_video_desde_archivo ||
						opcion_elegida == objFiltro.cargar_video_desde_camara
						)
					{
						dbx_filtrado.guardar_vid_filtrada = !dbx_filtrado.guardar_vid_filtrada;
						if (dbx_filtrado.guardar_vid_filtrada)
							SetWindowTextA(btn_guardar_filtrada, objFiltro.statMSG[objFiltro.grabando_video_filtrado].nombre);// "Grabando...");
						else
							SetWindowTextA(btn_guardar_filtrada, objFiltro.statMSG[objFiltro.detener_grabado_filtrado].nombre);//"Dejar de grabar");

					}
					break;
				}
			}

			break;
		}
	}
	return false;
}