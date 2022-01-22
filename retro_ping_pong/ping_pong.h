#ifndef PING_PONG_H_
#define PING_PONG_H_

#include <utility>
#include <windows.h>

class PingPong
{
private:
	enum
	{
		SCREEN_WIDTH = 128,
		SCREEN_HEIGHT = 64,
		PLAYER_RACKET_SIZE = 3,
		DISTANSE_FROM_BORDER_TO_RACKET = 2

	};


	std::pair<int, int> ball_cord;
	std::pair<double, double> ball_direction_vector;

	int y_cord_player_1;
	int y_cord_player_2;


	int screen_width;
	int screen_heigt;

	int player_racket_size;

	int distanse_from_border_to_racket;

	bool is_racket_cord(int x, int screen_width, int distanse_from_border_to_racket) const;
	bool is_racket_fill(int y, int y_cord_player, int player_racket_size) const;

	void clear();



public:
	enum {
		FIRST_PLAYER,
		SECOND_PLAYER
	};

	PingPong(int screen_width = SCREEN_WIDTH, int screen_height = SCREEN_HEIGHT, int player_racket_size = PLAYER_RACKET_SIZE, int distanse_from_border_to_racket = DISTANSE_FROM_BORDER_TO_RACKET);
	void drawGame();

	bool move_player_up(size_t player);
	bool move_player_down(size_t player);
	wchar_t* screen;

};

#endif //PING_PONG_H_
