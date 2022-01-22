#ifndef SCREEN_H_
#define SCREEN_H_

#include <windows.h>
#include <string>
#include <iostream>

#include "screen.h"

class Screen
{
private:
	int width;
	int height;

	wchar_t* screen;

	HANDLE hConsole;
	DWORD dwBytesWritten;

	void SetWindow(int Width, int Height);
public:
	Screen(int Width, int Height);
	~Screen();

	void upDate();
	void setPixel(int &x, int &y, char ch) const;
	void CoutCentered(std::string text);
	void drawBorder();
};
#endif //! SCREEN_H_

