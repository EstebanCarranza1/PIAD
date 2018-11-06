#pragma once
#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
class mod_picture
{
public:
	HBITMAP imgMnt;
	char pathDefault[MAX_PATH];
	int SizeWidth;
	int SizeHeight;
	int id;

	HBITMAP getImagen()
	{
		return imgMnt;
	}

	void setImagen(HBITMAP imagen)
	{
		this->imgMnt = imagen;
	}
	void setPathDefault()
	{
		//ERROR DEPURAR DESPUES
		HMODULE hModule = GetModuleHandleW(NULL);
		WCHAR path[MAX_PATH];
		GetModuleFileNameW(hModule, path, MAX_PATH);

		strcpy(this->pathDefault, convertWCHARtoCHAR(path));
	}
	void setPathDefault(char *path)
	{
		//SE VA A USAR POR MIENTRAS MIENTRAS SE RESUELVE EL PATH 
		strcpy(this->pathDefault, path);
	}
	char *getPath()
	{
		//setPathDefault();
		return pathDefault;
	}
	void setSize(int Width, int Height)
	{
		this->SizeWidth = Width;
		this->SizeHeight = Height;
	}
	int getSizeWidth()
	{
		return this->SizeWidth;
	}
	int getSizeHeight()
	{
		return this->SizeHeight;
	}
};
