#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>  
#include "convert.h"
#include "controls.h"
#include <windowsx.h>
#include "resource.h"
#include "ctrl_dbx_filtros.h"
#include "ctrl_dbx_conteo.h"
#include "ctrl_dbx_menu.h"
#pragma comment (lib, "Comctl32.lib")

//#pragma comment(lib,"opencv_world310d.lib")

using namespace cv;
using namespace std;



int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{

	DialogBox(dbx_menu.hInst, MAKEINTRESOURCE(DBX_MENU), NULL, reinterpret_cast<DLGPROC>(call_menu));
	return 0;
}