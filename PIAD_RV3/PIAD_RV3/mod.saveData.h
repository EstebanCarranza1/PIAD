#pragma once
#include <fstream>
#include <iostream>

using namespace std;

static class saveData
{
public:
	static void sendLog(uchar blue, uchar green, uchar red)
	{
		ofstream outLog;
		outLog.open("C:\\DATA\\log.tmp", ios::app);
			outLog << "rgb(";
			outLog << blue << ",";
			outLog << green << ",";
			outLog << red << "); \n";
		outLog.close();
	}
	static void sendLog(char data[255])
	{
		ofstream outLog;
		outLog.open("LOGS\\log.tmp", ios::out);
		outLog << data << "\n";
		outLog.close();
	}
};