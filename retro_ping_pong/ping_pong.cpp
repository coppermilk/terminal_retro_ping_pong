#include "ping_pong.h"
#include <iostream>

#ifndef DEBUG
#define DEBUG
#endif // !DEBUG

bool PingPong::is_racket_cord(int x, int screen_width, int distanse_from_border_to_racket) const
{
	return  (x == distanse_from_border_to_racket || x == screen_width - distanse_from_border_to_racket - 1);
}

bool PingPong::is_racket_fill(int y, int y_cord_player, int player_racket_size) const
{
	return (y_cord_player >= y) && (y_cord_player < y + player_racket_size);
}

void PingPong::clear()
{
#if defined _WIN32
	//system("cls");
	//setcur(0, 0);
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif

}

PingPong::PingPong(int screen_width, int screen_height, int player_racket_size, int distanse_from_border_to_racket)
{
	this->screen_width = screen_width;
	this->screen_heigt = screen_height;
	this->player_racket_size = player_racket_size;
	this->distanse_from_border_to_racket = distanse_from_border_to_racket;

	// midle of screen;
	y_cord_player_1 = y_cord_player_2 = (screen_height + player_racket_size - 1) /2;
	//wchar_t* screen = new wchar_t[20 * 10];
	//wmemset(screen, '\0', sizeof(screen));
}

void PingPong::drawGame()
{
	static	wchar_t* screen = new wchar_t[20 * 10];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	for (int y = 0; y < screen_heigt; y++) {
		for (int x = 0; x < screen_width; x++) {
			if (x == 0 || x == screen_width - 1) {
				//std::cout << "#";
				screen[y + x * screen_width] = '#';
			}
			else if (is_racket_cord(x, screen_width, distanse_from_border_to_racket) &&
				is_racket_fill(y, y_cord_player_1, player_racket_size)){
				screen[y + x * screen_width] = '*';
			}
			else {
				//std::cout << " ";
				screen[x + y * screen_heigt] = ' ';
			}
		
		}
		std::cout << "\n";
	}
	WriteConsoleOutputCharacter(hConsole, screen, screen_width * screen_heigt, { 0, 0 }, &dwBytesWritten);
}

bool PingPong::move_player_up(size_t player)
{
	bool is_success = false;

	if (player == FIRST_PLAYER) {
		y_cord_player_1++;
		is_success = true;
	}
	else if (player == SECOND_PLAYER) {
		y_cord_player_2++;
		is_success = true;
	}
	
	return is_success;
}

bool PingPong::move_player_down(size_t player)
{
	bool is_success = false;

	if (player == FIRST_PLAYER) {
		y_cord_player_1--;
		is_success = true;
	}
	
	else if (player == SECOND_PLAYER) {
		y_cord_player_2--;
		is_success = true;
	}
	
	return is_success;
}
