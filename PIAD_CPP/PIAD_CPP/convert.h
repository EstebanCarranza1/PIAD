#pragma once


#include <Windows.h>
wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
char *convertWCHARtoCHAR(WCHAR wChar[MAX_PATH])
{
	char Char[MAX_PATH];
	for (int i = 0; i < strlen(Char); i++)
		Char[i] = wChar[i];
	return Char;
}
