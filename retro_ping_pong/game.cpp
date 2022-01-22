#include "game.h"

// #pragma warning(disable : 4996)

void Game::upDateRocket()
{
	upDateRotect_player_1();
	upDateRocket_player_2();
}

void Game::upDateRotect_player_1()
{
	for (int y = y_cord_player_1; y != y_cord_player_1 - player_racket_size; y--) {
		screen.setPixel(distanse_from_border_to_racket, y, '#');
	}
	removeOldRocktData_player_1(y_cord_player_1);
}

void Game::upDateRocket_player_2()
{
	int x_distanse_to_up_date = width - distanse_from_border_to_racket - 1;

	for (int y = y_cord_player_2; y != y_cord_player_2 - player_racket_size; y--) {
		screen.setPixel(x_distanse_to_up_date, y, '#');
	}
	removeOldRocktData_player_2(y_cord_player_2);
}

void Game::removeOldRocktData_player_1(int y_cord_player_1)
{

	int y_pixel_to_clear_up = y_cord_player_1 - player_racket_size;
	int y_pixel_to_clear_down = y_cord_player_1 + 1;

	if (!(y_pixel_to_clear_up == 0)) {
		screen.setPixel(distanse_from_border_to_racket, y_pixel_to_clear_up, ' ');
	}

	if (!(y_pixel_to_clear_down == height - 1)) {
		screen.setPixel(distanse_from_border_to_racket, y_pixel_to_clear_down, ' ');

	}
}

void Game::removeOldRocktData_player_2(int y_cord_player_2)
{
	int y_pixel_to_clear_up = y_cord_player_2 - player_racket_size;
	int y_pixel_to_clear_down = y_cord_player_2 + 1;

	int x_distanse_to_delete_up = width - distanse_from_border_to_racket - 1;
	int x_distanse_to_detele_down = width - distanse_from_border_to_racket - 1;

	if (!(y_pixel_to_clear_up == 0)) {
		screen.setPixel(x_distanse_to_delete_up, y_pixel_to_clear_up, ' ');
	}

	if (!(y_pixel_to_clear_down == height - 1)) {
		screen.setPixel(x_distanse_to_detele_down, y_pixel_to_clear_down, ' ');

	}

}

void Game::upDateBall()
{
	rounded_ball_cord.first = (int)ball_cord.first;
	rounded_ball_cord.second = (int)ball_cord.second;

	screen.setPixel(rounded_ball_cord.first, rounded_ball_cord.second, ' ');

	if ((ball_cord.first <= player_racket_size) && is_on_rocket(ball_cord.second, y_cord_player_1)) {
		ball_direction_vector.first *= -1;
		score_player_1++;
	}

	if ((ball_cord.first >= width - player_racket_size) && is_on_rocket(ball_cord.second, y_cord_player_2)) {
		ball_direction_vector.first *= -1;
		score_player_2++;

	}


	if (ball_cord.second <= 2 || ball_cord.second >= height - 1 - 1) {
		ball_direction_vector.second *= -1;

	}

	ball_cord.first += ball_direction_vector.first;
	ball_cord.second += ball_direction_vector.second;

	//char msgbuf[80];
	//sprintf(msgbuf, "first %f\n", ball_direction_vector.first);
	//OutputDebugStringA(msgbuf);
	//sprintf(msgbuf, "second %f\n", ball_direction_vector.second);
	//OutputDebugStringA(msgbuf);

	rounded_ball_cord.first = (int)ball_cord.first;
	rounded_ball_cord.second = (int)ball_cord.second;

	screen.setPixel(rounded_ball_cord.first, rounded_ball_cord.second, 'O');
}

void Game::setRandBallImpuls()
{
	switch (rand() % 3)
	{
	case 0:
		ball_direction_vector.second = 0.05;
		break;
	
	case 1:
		ball_direction_vector.second = 0.15;
		break;

	case 2:
		ball_direction_vector.second = -0.2;
		break;
	default:
		break;
	}
}


bool Game::is_move_possible(int y, int& height) const
{
	return ((y > 0) && (y < height - 1));
}

bool Game::is_on_rocket(int y, int y_cord_player)
 {
	if (y <= y_cord_player && y > y_cord_player - player_racket_size) {
		setRandBallImpuls();
		return true;
	}
	else {
		is_game_over = true;
		return false;
	}

}



Game::Game(int width, int height, int player_racket_size, int distanse_from_border_to_racket) : screen(width, height)
{
	this->width = width;
	this->height = height;
	this->player_racket_size = player_racket_size;
	this->distanse_from_border_to_racket = distanse_from_border_to_racket;
	last_move_player_1 = last_move_player_2 = 0;

	// At the middle
	y_cord_player_1 = y_cord_player_2 = (height + player_racket_size - 1) / 2;
	score_player_1 = score_player_2 = 0;
	ball_cord.first = width / 2;
	ball_cord.second = height / 2;

	ball_direction_vector.first =  0.9;
	ball_direction_vector.second = -0.1;

	is_game_over = false;

}

void Game::upDate()
{
	upDateRocket();
	upDateBall();
	screen.upDate();
}

void Game::reset()
{	
	screen.drawBorder();
	last_move_player_1 = last_move_player_2 = 0;

	// At the middle screen
	y_cord_player_1 = y_cord_player_2 = (height + player_racket_size - 1) / 2;
	score_player_1 = score_player_2 = 0;
	ball_cord.first = width / 2;
	ball_cord.second = height / 2;

	// Game setup
	ball_direction_vector.first = 0.9;
	ball_direction_vector.second = 0.1;
}

void Game::showResult()
{
	std::string result = "GAME OVER";
	screen.CoutCentered(result);
}

void Game::autoPlay()
{
	if (y_cord_player_1 > ball_cord.second 
		&& y_cord_player_1 - player_racket_size /2 >= ball_cord.second 
		&& (rand() % 10) 
		&& ball_cord.first < width /2){

		move_up_player_1();
	}
	else if (y_cord_player_1 < ball_cord.second && (rand() % 10)) {

		move_down_player_1();
	}

	if (y_cord_player_2 > ball_cord.second 
		&& y_cord_player_2 - player_racket_size /2 >= ball_cord.second 
		&& (rand() % 10)
		&& ball_cord.first > width / 2){ 

		move_up_player_2();
	}
	else if (y_cord_player_2  < ball_cord.second && (rand() % 10)) {

		move_down_player_2();
	}
}


void Game::move_up_player_1()
{
	if (is_move_possible(y_cord_player_1 - player_racket_size, height)) {
		y_cord_player_1--;
	}
}

void Game::move_down_player_1()
{
	if (is_move_possible(y_cord_player_1 + 1, height)) {
		y_cord_player_1++;
	}
}

void Game::move_up_player_2()
{
	if (is_move_possible(y_cord_player_2 - player_racket_size, height)) {
		y_cord_player_2--;
		}
}

void Game::move_down_player_2()
{
	if (is_move_possible(y_cord_player_2 + 1, height)) {
		y_cord_player_2++;
	}
}



