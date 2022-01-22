#include <iostream>
#include <windows.h>
#include <conio.h>
#include "game.h"

int main() {
	const int width = 32;
	const int height = 32;
	const int player_racket_size = 5;
	const int distanse_from_border_to_racket = 2;

	// Restart game indefinitely
	while (1) {

		Game g(width, height, player_racket_size, distanse_from_border_to_racket);
		while (!(g.is_game_over)) { if (_kbhit()) {
				switch (_getch()) {
				case ';':
					g.move_up_player_1();
					break;
				case 'a':
					g.move_down_player_1();
					break;
				case ',':
					g.move_up_player_2();
					break;
				case 'o':
					g.move_down_player_2();
					break;
				}
			}
			g.upDate();
			g.autoPlay();
			Sleep(1);
		}
		g.showResult();
		Sleep(2000);
	}	
}

