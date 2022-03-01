#ifndef SNAKE_H
#define SNAKE_H
#include <vector>
#include <string>

using namespace std;

class Snake {
public:
	/**@brief Different move directions. */
	enum Direction {
		NORTH,
		SOUTH,
		EAST,
		WEST
	};

private:
	/**@brief Where the snake is currently facing. */
	Direction facing;

	/**@brief Spawn position. */
	pair<int,int> spawn;

	/**@brief Head position. */
	pair<int,int> head;

	/**@brief Position of each tail segment. */
	vector<pair<int,int>> tail;

	/**@brief Amount of lifes remaining. */
	int lifes;

	/**@brief Amount of food already eaten. */
	int food_eaten;

	/**@brief Amount of steps taken to reach a food. */
	int steps;

	/**@brief Score currently made. */
	int score;

public:
	/**@brief Snake constructor.
         * @param layout Level layout extracted by Parser.
         */
	Snake(vector<string> layout);

	/**@brief Getter for facing.
	 * @return Value of facing.
         */
	Direction get_facing() const;

	/**@brief Getter for opposite direction of facing.
	 * @return Value of opposite of facing.
         */
	Direction get_opposite_facing() const;

	/**@brief Getter for head.first (Y).
	 * @return Value of head.first.
         */
	int get_head_y() const;

	/**@brief Getter for head.second (X).
	 * @return Value of head.second.
         */
	int get_head_x() const;

	/**@brief Getter for lifes.
	 * @return Value of lifes.
         */
	int get_lifes() const;

	/**@brief Getter for food_eaten.
	 * @return Value of food_eaten.
         */
	int get_food_eaten() const;

	/**@brief Getter for printable head character.
	 * @return Head character based on snake's facing.
         */
	char get_head_icon() const;

	/**@brief Getter for steps.
	 * @return Value of steps.
         */
	int get_steps() const;

	/**@brief Getter for score.
	 * @return Value of score.
         */
	int get_score() const;

	/**@brief Checks if head is on a map position.
	 * @param y Y value of a map's position.
	 * @param x X value of a map's position.
	 * @return True if head is on the position; false if not.
         */
	bool is_head(int y, int x) const;

	/**@brief Checks if any segment of tail is on a map position.
	 * @param y Y value of a map's position.
	 * @param x X value of a map's position.
	 * @return True if any segment is on the position; false if not.
         */
	bool is_tail(int y, int x) const;

	/**@brief Increases score based on snake's steps.
         */
	void increase_score();

	/**@brief Adds a new segment to tail.
         */
	void grow();

	/**@brief Moves the snake towards a direction.
	 * @param direction Direction to move to.
	 * @param eat Wether the snake will eat or not after moving.
	 * @return Void; exists out if direction is invalid.
         */
	void move(Direction direction, bool eat);

	/**@brief Erases whole tail and respawns snake at its spawn.
         */
	void respawn();
};

#endif

