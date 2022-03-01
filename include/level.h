#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include "snake.h"

using namespace std;

class Level {
private:
	/**@brief Pointer for snake. */
	const Snake* snake;

	/**@brief Map of characters. */
	vector<string> map;

	/**@brief Spawn position. */
	pair<int,int> spawn;

	/**@brief Map's lengt. */
	int lines;

	/**@brief Map's width. */
	int columns;

	/**@brief Amount of food necessary for win. */
	int food_count;

public:
	/**@brief Level constructor.
         * @param layout Level layout extracted by Parser.
         * @param snake Snake pointer.
         */
	Level(vector<string> layout, Snake* snake);

	/**@brief Getter for spawn.first (Y).
         * @return Value of spawn.first.
         */
	int get_spawn_y() const;

	/**@brief Getter for spawn.second (X).
         * @return Value of spawn.second.
         */
	int get_spawn_x() const;

	/**@brief Getter for lines.
         * @return Value of lines.
         */
	int get_lines() const;

	/**@brief Getter for columns.
         * @return Value of columns.
         */
	int get_columns() const;

	/**@brief Getter for food_count.
         * @return Value of food_count.
         */
	int get_food_count() const;

	/**@brief Getter for character on a map position.
         * @param y Y value of a map's position.
         * @param x X value of a map's position.
         * @return Character on the position.
         */
	char get_position(int y, int x) const;

	/**@brief Formats map into a printable string.
         * @return Formatted string.
         */
	string generate_map() const;

	/**@brief Erases food from map and respawns it somewhere else valid.
	 * @return Void; exits out if all map positions were tested and failed.
         */
	void respawn_food();

	/**@brief Checks if snake has hit a wall or itself.
	 * @return True if snake did die; false if not.
         */
	bool snake_died() const;

	/**@brief Checks if snake will eat after moving to a direction.
	 * @return True if snake will eat; false if not.
         */
	bool snake_will_eat(Snake::Direction direction) const;

	/**@brief Checks if food is over the spawn point.
	 * @return True if it is; false if it isn't.
         */
	bool food_on_spawn() const;
};

#endif

