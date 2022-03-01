#ifndef AI_H
#define AI_H
#include <vector>
#include "snake.h"
#include "level.h"

using namespace std;

class AI {
private:
	/**@brief Pointer for the snake. */
	const Snake* snake;

	/**@brief Pointer for the level. */
	const Level* level;

	/**@brief List of directions which lead snake to the food. */
	vector<Snake::Direction> solution;

	/**@brief List of positions the snake has stepped on. */
	vector<pair<int,int>> track;

public:
	/**@brief AI constructor.
	 * @param snake Snake pointer.
	 * @param snake Level pointer.
         */
	AI(Snake* snake, Level* level);

	/**@brief Checks if AI has a solution.
         * @return True if there's a solution; false if not.
         */
	bool has_solution() const;

	/**@brief Adds a single random valid move in solution; NORTH if no valid move.
         */
	void random_direction();

	/**@brief Sets the ground for recursive function find_solution(int y, int x).
	 * @return Whatever find_solution(int y, int x) returns.
         */
	bool find_solution();

	/**@brief Adds a sequence of winning moves in solution; empties solution
	 * if no solution was found. Calculates it iteratively.
	 * @return True if a solution was found; false otherwise.
         */
	bool iterative_solution();

	/**@brief Outputs, and then removes, next direction from solution.
         * @return Next direction from solution; exits out if no next direction.
         */
	Snake::Direction next_move();

private:

	/**@brief Adds a sequence of winning moves in solution; empties solution
	 * if no solution was found. Calculates it recursively.
	 * @param y Y value of a map's position.
	 * @param x X value of a map's position.
	 * @return True if a solution was found; false otherwise.
         */
	bool find_solution(int y, int x);
};

#endif

