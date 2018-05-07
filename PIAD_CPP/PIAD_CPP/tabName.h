#pragma once
class tabName
{
	char name[255];
	wchar_t wtext[20];
	LPWSTR nameL;

public:
	tabName()
	{

	}
	tabName(char name[255])
	{
		strcpy(this->name, name);
		mbstowcs(wtext, name, strlen(name) + 1);
		nameL = wtext;
	}


	void setName(char name[255])
	{
		strcpy(this->name, name);
		mbstowcs(wtext, name, strlen(name) + 1);
		nameL = wtext;
	}
	LPWSTR getNameLPWSTR()
	{
		return this->nameL;
	}

};