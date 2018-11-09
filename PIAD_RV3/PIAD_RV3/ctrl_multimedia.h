#pragma once
#include <Windows.h>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "mod.picture.h"
#include "convert.h"
#include <iostream>
//#pragma comment(lib,"opencv_world310d.lib")


using namespace cv;
using namespace std;

static class mod_multimedia
{
public:
	static int guardar_imagen(Mat mat, HWND hWnd, mod_picture image)//HBITMAP hPictureBox, int SizeWidth, int SizeHeight, char pathImg[])
	{
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);

		try {


			imwrite(image.pathDefault, mat, compression_params);
			image.setImagen((HBITMAP)LoadImage(NULL, convertCharArrayToLPCWSTR(image.pathDefault), IMAGE_BITMAP, image.getSizeWidth(), image.getSizeHeight(), LR_LOADFROMFILE));
			SendDlgItemMessage(hWnd, image.id, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image.getImagen());

			return 0;
		}
		catch (runtime_error& ex) {
			fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
			return 1;
		}
	}

	static class imagen
	{
	public:
		static Mat LoadOfPC(char path[255])
		{
			string imageName = (path); // by default
			Mat image;
			image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file
			return image;
		}
		static int SaveOfPC(Mat mat, char path[255])
		{
			vector<int> compression_params;
			compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
			compression_params.push_back(9);
			try 
			{
				imwrite(path, mat, compression_params);	
				return 0;
			}
			catch (runtime_error& ex) {
				fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
				return 1;
			}
		}
		static void getOfCamera()
		{

		}
		static void showOfCamera()
		{

		}
	};
	
	static class video
	{
		static void getLocal()
		{

		}
		static void setLocal()
		{

		}
		static void setCamera()
		{

		}
		static void getCamera()
		{

		}
	};


};