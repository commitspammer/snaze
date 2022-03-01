#include <vector>
#include <string>
#include "snake.h"

using namespace std;

Snake::Snake(vector<string> layout)
{
	this->facing = NORTH;
	this->lifes = 5;
	this->food_eaten = 0;
	this->steps = 0;
	this->score = 0;

	layout.erase(layout.begin());
	for (unsigned long int i = 0; i < layout.size(); i++) {
		for (unsigned long int j = 0; j < layout[i].size(); j++) {
			if (layout[i][j] == '*') {
				this->head = make_pair(i, j);
				this->spawn = make_pair(i, j);
			}
		}
	}
}

Snake::Direction Snake::get_facing() const
{
	return this->facing;
}

Snake::Direction Snake::get_opposite_facing() const
{
	switch (this->facing) {
	case NORTH:
		return SOUTH;
	case SOUTH:
		return NORTH;
	case EAST:
		return WEST;
	case WEST:
		return EAST;
	}
	return NORTH;
}

int Snake::get_head_y() const
{
	return this->head.first;
}

int Snake::get_head_x() const
{
	return this->head.second;
}

int Snake::get_lifes() const
{
	return this->lifes;
}

int Snake::get_food_eaten() const
{
	return this->food_eaten;
}

char Snake::get_head_icon() const
{
	switch (this->facing) {
	case NORTH:
		return '^';
	case SOUTH:
		return 'v';
	case EAST:
		return '>';
	case WEST:
		return '<';
	}
	return 'x';
}

int Snake::get_steps() const
{
	return this->steps;
}

int Snake::get_score() const
{
	return this->score;
}

bool Snake::is_head(int y, int x) const
{
	if (this->head.first == y && this->head.second == x)
		return true;
	return false;
}

bool Snake::is_tail(int y, int x) const
{
	for (auto& t : this->tail){
		if (t.first == y && t.second == x)
			return true;
	}
	return false;
}

void Snake::increase_score()
{
	if (this->steps < 50)
		this->score += (100-(this->steps*2))/10;
	else
		this->score += 1;
}

void Snake::grow()
{
	if (this->tail.empty())
		this->tail.push_back(this->head);
	else
		this->tail.push_back(this->tail.back());
}

void Snake::move(Snake::Direction direction, bool eat)
{
	this->steps++;

	this->tail.insert(this->tail.begin(), this->head);
	this->tail.pop_back();

	if (direction == get_opposite_facing())
		exit(1);
	switch (direction) {
	case NORTH:
		this->head.first--;
		this->facing = NORTH;
		break;
	case SOUTH:
		this->head.first++;
		this->facing = SOUTH;
		break;
	case WEST:
		this->head.second--;
		this->facing = WEST;
		break;
	case EAST:
		this->head.second++;
		this->facing = EAST;
		break;
	}

	if (eat) {
		this->steps = 0;
		this->food_eaten++;
	}
}

void Snake::respawn()
{
	this->lifes--;
	this->facing = NORTH;
	this->head.first = this->spawn.first;
	this->head.second = this->spawn.second;
	this->tail.clear();
	this->steps = 0;
}
