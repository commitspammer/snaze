#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "parser.h"
#include "game.h"

using namespace std;

int error(string description)
{
	cout << "ERROR: " << description << endl;
	return -1;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return error("Missing file");

	Parser parser;

	string file(argv[1]);
	if (!parser.try_open_file(file))
		return error("Invalid file path");

	string mode = "snake";
	if (argc > 2) {
		string tmp(argv[2]);
		if (!parser.parse_mode(tmp))
			return error("Invalid game mode");
		mode = tmp;
	}

	parser.separate_layouts_from_level_file(file);
	vector<string> layout;
	while (parser.get_next_layout(&layout)) {
		Snake* snake = new Snake(layout);
		Level* level = new Level(layout, snake);
		AI* ai = new AI(snake, level);
		Game* game = new Game(mode, snake, level, ai);

		game->start();

		delete snake;
		delete level;
		delete ai;
		delete game;
	}
	return 0;
}
