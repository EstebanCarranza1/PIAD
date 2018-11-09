#pragma once
#include <Windows.h>
#include "resource.h"
#include "OpenFileDialog.h"
#include "e1.h"
#include "mod.picture.h"
#include "mod.filtro.h"


mod_picture picNormal, picFiltrada;
mod_picture picMenu;
HWND cbx_filtros, cbx_forma, txt_mensajes, txt_path;
HWND btn_examinar, btn_recargar;
HWND btn_iniciar_camara, btn_capturar;
HWND btn_configurar_filtro, btn_aplicar_filtro;
HWND btn_guardar_normal, btn_guardar_filtrada;

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

			objFiltro.inicializar_nombres();
			for (int i = 0; i < objFiltro.max_nomFiltro; i++)
				SendMessageA(cbx_filtros, CB_ADDSTRING, 0, (LPARAM)(objFiltro.propFiltro[i].titulo));
			for(int i=0;i< objFiltro.max_formaFiltrado;i++)
				SendMessageA(cbx_forma, CB_ADDSTRING, 0, (LPARAM)(objFiltro.formaFiltrado[i].nombre));
			SetWindowTextA(txt_mensajes, (LPCSTR)(objFiltro.filterMSG[0].nombre));

			SendMessageA(cbx_forma, CB_SETCURSEL, 0, 0);
			SendMessageA(cbx_filtros, CB_SETCURSEL, 0, 0);

			EnableWindow(txt_path, false);
			EnableWindow(btn_recargar, false);
			EnableWindow(btn_examinar, false);
			EnableWindow(btn_iniciar_camara, false);
			EnableWindow(btn_capturar, false);
			EnableWindow(btn_configurar_filtro, false);
			EnableWindow(btn_aplicar_filtro, false);
			EnableWindow(btn_guardar_normal, false);
			EnableWindow(btn_guardar_filtrada, false);
			EnableWindow(cbx_filtros, false);
			

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
					if (objFiltro.formaFiltrado[0].activado)
					{
						EnableWindow(cbx_filtros, false);
						EnableWindow(txt_path, false);
						EnableWindow(btn_recargar, false);
						EnableWindow(btn_examinar, false);
						EnableWindow(btn_iniciar_camara, false);
						EnableWindow(btn_capturar, false);
					}
					if (objFiltro.formaFiltrado[1].activado || objFiltro.formaFiltrado[3].activado)
					{
						EnableWindow(txt_path, true);
						EnableWindow(btn_recargar, true);
						EnableWindow(btn_examinar, true);
						EnableWindow(cbx_filtros, true);
					}
					else
					{
						EnableWindow(txt_path, false);
						EnableWindow(btn_recargar, false);
						EnableWindow(btn_examinar, false);
					}
					if (objFiltro.formaFiltrado[2].activado || objFiltro.formaFiltrado[4].activado)
					{
						EnableWindow(btn_iniciar_camara, true);
						EnableWindow(btn_capturar, true);
						EnableWindow(cbx_filtros, true);
					}
					else
					{
						EnableWindow(btn_iniciar_camara, false);
						EnableWindow(btn_capturar, false);
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
					SetWindowTextA(txt_mensajes, (LPCSTR)(objFiltro.filterMSG[3].nombre));
					start_record(hWnd, picNormal, picFiltrada);
			
					//imgMnt = cambiarPic();
					//SendDlgItemMessage(hWnd, PIC_VIDEOCAMERA, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imgMnt);
					break;
				}
				case IDCANCEL:
				{
					EndDialog(hWnd, true);
					break;
				}
				case BTN_EXAMINAR:
				{
			
					LPCWSTR path = getPathToImage(hWnd);
					char pathCHAR[255];
					strcpy_s(pathCHAR, convertLPCWSTRtoCHAR(path));
					
					if (path != NULL)
					{
						
						SetWindowTextA(txt_path, (LPCSTR)pathCHAR);
						SetWindowTextA(txt_mensajes, (LPCSTR)objFiltro.filterMSG[0].nombre);
						//picNormal.setImagen((HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 300, 300, LR_LOADFROMFILE));
						//SendDlgItemMessage(hWnd, PIC_VIDEOCAMERA, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)picNormal.getImagen());
					}
					
					break;
				}
				case BTN_RECARGAR:
				{
					char pathCHAR[255];
					GetWindowTextA(txt_path, pathCHAR, 255);
					cargar_imagen(pathCHAR);
				}
				break;
				case BTN_APLICAR_FILTRO:
				{
					//DialogBox(dbx_menu.hInst, MAKEINTRESOURCE(DBX_CONSOLE), NULL, reinterpret_cast<DLGPROC>(call_console));
					//lbx_console = GetDlgItem(hWnd_dbx_console, LBX_CONSOLE);
					//SendMessageA(lbx_console, LB_INSERTSTRING, 0, (LPARAM)"ctrl_dbx_filtros");
				}
				break;
			}
			break;
		}
	}
	return false;
}