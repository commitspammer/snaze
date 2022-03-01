#include <algorithm>
#include <fstream>
#include "ai.h"
#include "snake.h"
#include "level.h"
#include "randengine.h"

using namespace std;

AI::AI(Snake* snake, Level* level)
{
	this->snake = snake;
	this->level = level;
}

bool AI::has_solution() const
{
	if (this->solution.empty())
		return false;
	return true;
}

void AI::random_direction()
{
	RandEngine engine(Snake::Direction::NORTH, Snake::Direction::WEST);
	int i, j;
	vector<int> perm = engine.generate_permutation();
	for (auto& n : perm) {
		if (n == this->snake->get_opposite_facing())
			continue;
		i = this->snake->get_head_y();
		j = this->snake->get_head_x();
		switch (n) {
		case Snake::Direction::NORTH:
			i--; break;
		case Snake::Direction::SOUTH:
			i++; break;
		case Snake::Direction::EAST:
			j++; break;
		case Snake::Direction::WEST:
			j--; break;
		}
		if (i < 0 || i >= this->level->get_lines() || j < 0 || j >= this->level->get_columns())
			continue;
		if (level->get_position(i, j) != '#' && !snake->is_tail(i, j)) {
			this->solution.push_back((Snake::Direction)n);
			return;
		}
	}
	this->solution.push_back(this->snake->get_facing());
}

bool AI::find_solution()
{
	this->track.clear();
	this->solution.clear();
	int i = 0, j = 0;
	switch (this->snake->get_facing()) {
	case Snake::Direction::NORTH:
		i++; break;
	case Snake::Direction::SOUTH:
		i--; break;
	case Snake::Direction::EAST:
		j--; break;
	case Snake::Direction::WEST:
		j++; break;
	}
	this->track.push_back(make_pair(this->snake->get_head_y()+i, this->snake->get_head_x()+j));
	return find_solution(this->snake->get_head_y(), this->snake->get_head_x());
}

bool AI::find_solution(int y, int x)
{
	int l = this->level->get_lines();
	int c = this->level->get_columns();
	if (y < 0 || y >= l || x < 0 || x >= c)
		return false;
	if (this->level->get_position(y, x) == '@' && this->track.size() > 2)
		return true;
	if (find(this->track.begin(), this->track.end(), make_pair(y, x)) != this->track.end())
		return false;
	if (this->level->get_position(y, x) != ' ' || this->snake->is_tail(y, x))
		return false;

	this->track.push_back(make_pair(y, x));

	if (find_solution(y-1, x)) {
		this->solution.push_back(Snake::Direction::NORTH);
		return true;
	}
	if (find_solution(y+1, x)) {
		this->solution.push_back(Snake::Direction::SOUTH);
		return true;
	}
	if (find_solution(y, x+1)) {
		this->solution.push_back(Snake::Direction::EAST);
		return true;
	}
	if (find_solution(y, x-1)) {
		this->solution.push_back(Snake::Direction::WEST);
		return true;
	}

	this->track.pop_back();
	return false;
}

bool AI::iterative_solution()
{
	this->track.clear();
	this->solution.clear();
	switch (this->snake->get_facing()) {
	case Snake::Direction::NORTH:
		this->track.push_back(make_pair(this->snake->get_head_y()+1, this->snake->get_head_x())); break;
	case Snake::Direction::SOUTH:
		this->track.push_back(make_pair(this->snake->get_head_y()-1, this->snake->get_head_x())); break;
	case Snake::Direction::EAST:
		this->track.push_back(make_pair(this->snake->get_head_y(), this->snake->get_head_x()-1)); break;
	case Snake::Direction::WEST:
		this->track.push_back(make_pair(this->snake->get_head_y(), this->snake->get_head_x()+1)); break;
	}

	vector<pair<int,int>> deadend;
	int l = this->level->get_lines();
	int c = this->level->get_columns();
	int y = this->snake->get_head_y();
	int x = this->snake->get_head_x();
	do {
		if (this->level->get_position(y, x) == '@')
			return true;

		this->track.push_back(make_pair(y, x));

		this->solution.insert(this->solution.begin(), Snake::Direction::NORTH);
		y--;
		if (y >= 0 && y < l && x >= 0 && x < c) {
			if (level->get_position(y, x) == ' ' || level->get_position(y, x) == '@') {
				if (find(this->track.begin(), this->track.end(), make_pair(y, x)) == this->track.end()
				    && find(deadend.begin(), deadend.end(), make_pair(y, x)) == deadend.end())
					continue;
			}
		}
		this->solution.erase(this->solution.begin());
		y++;
		this->solution.insert(this->solution.begin(), Snake::Direction::SOUTH);
		y++;
		if (y >= 0 && y < l && x >= 0 && x < c) {
			if (level->get_position(y, x) == ' ' || level->get_position(y, x) == '@') {
				if (find(this->track.begin(), this->track.end(), make_pair(y, x)) == this->track.end()
				    && find(deadend.begin(), deadend.end(), make_pair(y, x)) == deadend.end())
					continue;
			}
		}
		this->solution.erase(this->solution.begin());
		y--;
		this->solution.insert(this->solution.begin(), Snake::Direction::EAST);
		x++;
		if (y >= 0 && y < l && x >= 0 && x < c) {
			if (level->get_position(y, x) == ' ' || level->get_position(y, x) == '@') {
				if (find(this->track.begin(), this->track.end(), make_pair(y, x)) == this->track.end()
				    && find(deadend.begin(), deadend.end(), make_pair(y, x)) == deadend.end())
					continue;
			}
		}
		this->solution.erase(this->solution.begin());
		x--;
		this->solution.insert(this->solution.begin(), Snake::Direction::WEST);
		x--;
		if (y >= 0 && y < l && x >= 0 && x < c) {
			if (level->get_position(y, x) == ' ' || level->get_position(y, x) == '@') {
				if (find(this->track.begin(), this->track.end(), make_pair(y, x)) == this->track.end()
				    && find(deadend.begin(), deadend.end(), make_pair(y, x)) == deadend.end())
					continue;
			}
		}
		this->solution.erase(this->solution.begin());
		x++;

		deadend.push_back(make_pair(y, x));
		do {
			if (this->track.size() < 2)
				return false;

			y = (track.end()-1)->first;
			x = (track.end()-1)->second;

			this->track.pop_back();

			if (level->get_position(y-1, x) == ' ' || level->get_position(y-1, x) == '@') {
				if (find(this->track.begin(), this->track.end(), make_pair(y-1, x)) == this->track.end()
			    	    && find(deadend.begin(), deadend.end(), make_pair(y, x)) == deadend.end())
					break;
			}
			if (level->get_position(y+1, x) == ' ' || level->get_position(y+1, x) == '@') {
				if (find(this->track.begin(), this->track.end(), make_pair(y+1, x)) == this->track.end()
			    	    && find(deadend.begin(), deadend.end(), make_pair(y, x)) == deadend.end())
					break;
			}
			if (level->get_position(y, x+1) == ' ' || level->get_position(y, x+1) == '@') {
				if (find(this->track.begin(), this->track.end(), make_pair(y, x+1)) == this->track.end()
			    	    && find(deadend.begin(), deadend.end(), make_pair(y, x)) == deadend.end())
					break;
			}
			if (level->get_position(y, x-1) == ' ' || level->get_position(y, x-1) == '@') {
				if (find(this->track.begin(), this->track.end(), make_pair(y, x-1)) == this->track.end()
			    	    && find(deadend.begin(), deadend.end(), make_pair(y, x)) == deadend.end())
					break;
			}

			deadend.push_back(make_pair(y, x));
			if (!this->solution.empty())
				this->solution.erase(this->solution.begin());
		} while (true);
	} while (true);
}

Snake::Direction AI::next_move()
{
	if (this->solution.empty())
		exit(1);
	Snake::Direction move = this->solution.back();
	this->solution.pop_back();
	return move;
}
