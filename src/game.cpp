#include <chrono>
#include <thread>
#include "game.h"
#include "snake.h"
#include "level.h"
#include "ai.h"
#include "uiengine.h"

using namespace std;

Game::Game(string mode, Snake* snake, Level* level, AI* ai) : ui(snake, level)
{
	this->snake = snake;
	this->level = level;
	this->ai = ai;

	this->state = INTRO;
	this->mode = mode;
	this->ai_input = Snake::Direction::NORTH;
	this->frame_count = 0;
}

void Game::get_input()
{
	if (!this->ai->has_solution())
		this->ai->find_solution();
		//this->ai->iterative_solution();

	if (!this->ai->has_solution())
		this->ai->random_direction();

	this->ai_input = this->ai->next_move();
}

void Game::update()
{
	if (this->level->snake_died()) {
		this->snake->respawn();
		if (this->level->food_on_spawn())
			this->level->respawn_food();
		return;
	}

	if (this->snake->get_lifes() <= 0) {
		this->state = GAME_OVER;
		return;
	}

	if (this->snake->get_food_eaten() >= this->level->get_food_count()) {
		this->state = GAME_OVER;
		return;
	}

	if (this->level->snake_will_eat(this->ai_input)) {
		if (this->mode == "snake")
			this->snake->grow();
		this->snake->increase_score();
		this->snake->move(this->ai_input, true);
		this->level->respawn_food();
	} else {
		this->snake->move(this->ai_input, false);
	}
}

void Game::render()
{
	this->ui.clear_screen();
	switch (this->state) {
	case INTRO:
		this->ui.clear_screen();
		this->ui.icon();
		break;
	case RUNNING:
		this->ui.stats();
		this->ui.print(this->level->generate_map());
		break;
	case GAME_OVER:
		this->ui.victory_or_defeat();
		break;
	}
	this->frame_count++;
}

void wait(int ms)
{
        this_thread::sleep_for(chrono::milliseconds(ms));
}

void Game::start()
{
	this->state = INTRO;
	render();
	wait(2000);
	this->state = RUNNING;
	render();
	wait(1000);
	while (this->state != GAME_OVER) {
		get_input();
		update();
		render();
		wait(250);
	}
	wait(1750);
}
