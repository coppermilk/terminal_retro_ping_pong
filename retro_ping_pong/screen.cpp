#include "screen.h"
#include <string>

void Screen::SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
	SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

Screen::Screen(int Width, int Height)
{
	this->width = Width;
	this->height = Height;

	SetWindow(Width, Height);

	screen = new wchar_t[Width * Height + 1];
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	dwBytesWritten = 0;

	drawBorder();
}

void Screen::upDate()
{
	WriteConsoleOutputCharacter(hConsole, screen, width * height, { 0, 0 }, &dwBytesWritten);
}

void Screen::drawBorder()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			if (((y == 0) || (y == height - 1)) && ((x == 0) || (x == width - 1))) {
				setPixel(x, y, '+');
			}
			else if (y == 0 || y == height - 1) {
				setPixel(x, y, '-');
			}
			else {
				setPixel(x, y, ' ');
			}


		}
	}


}

Screen::~Screen()
{
	delete[] screen;
}

void Screen::setPixel(int &x, int &y, char ch) const
{
	screen[x + y * width] = ch;
}

void Screen::CoutCentered(std::string text) {
	//drawBorder();
	int strlen = text.size();
	int x_mid_start = (width - strlen - 1) / 2;
	int y_mid_start = height / 2;
	char ch;
	
	for (int i = 0; i < strlen; i++) {
		x_mid_start++;
		ch = text[i];
		setPixel(x_mid_start, y_mid_start,  ch);
	}

	upDate();
}
