#include <Windows.h>
#ifndef objects
#define objects
class _objects
{
public :
	
	class button
	{
	public:
		float posX = 0, posY = 0;
		float width = 10, height = 10;
		HWND *parentWindow;
		LPCWSTR text;
		HWND btn;
		DWORD estilo = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON;
		button()
		{

		}

		button(HWND *_parentWindow, LPCWSTR _text, float _posX, float _posY, float _width, float _height)
		{
			posX = _posX;
			posY = _posY;
			width = _width;
			height = _height;
			text = _text;
			parentWindow = _parentWindow;

			this->btn = CreateWindow(
				L"BUTTON",  // Predefined class; Unicode assumed 
				text,      // Button text 
				estilo,  // Styles 
				_posX,         // x position 
				_posY,         // y position 
				_width,        // Button width
				_height,        // Button height
				*parentWindow,     // Parent window
				NULL,       // No menu.
				(HINSTANCE)GetWindowLong(*parentWindow, GWL_HINSTANCE),
				NULL);
		}
		
		
	};
};

#endif // !_controls
