#ifndef GAME_H_
#define GAME_H_

#include <utility>
#include <iostream>

#include "screen.h"
#include "stdio.h"

class Game
{
private:
	int width;
	int height;

	int y_cord_player_1;
	int y_cord_player_2;

	int player_racket_size;
	int distanse_from_border_to_racket;

	int last_move_player_1;
	int last_move_player_2;

	Screen screen;

	std::pair<double, double> ball_cord;
	std::pair<double, double> ball_direction_vector;
	std::pair<int, int> rounded_ball_cord;

	void upDateRocket();

	//     1st     2nd
	//	|	|
	//
	void upDateRotect_player_1();
	void upDateRocket_player_2();

	void removeOldRocktData_player_1(int y);
	void removeOldRocktData_player_2(int y);
	
	void upDateBall();
	void setRandBallImpuls();

	bool is_move_possible(int y, int &height) const;
	bool is_on_rocket(int y, int y_cord_player);
public:
	Game(int width, int height, int player_racket_size, int distanse_from_border_to_racket);

	int score_player_1;
	int score_player_2;

	void upDate();
	void reset();
	void showResult();
	void autoPlay();

	void move_up_player_1();
	void move_down_player_1();

	void move_up_player_2();
	void move_down_player_2();
	bool is_game_over;
};

#endif // !GAME_H_

