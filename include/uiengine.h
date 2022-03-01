#ifndef UIENGINE_H
#define UIENGINE_H
#include <string>
#include "snake.h"
#include "level.h"

using namespace std;

class UIEngine {
private:
	/**@brief Pointer for the snake. */
	const Snake* snake;

	/**@brief Pointer for the level. */
	const Level* level;

public:
	/**@brief UIEngine constructor.
         * @param snake Snake pointer.
         * @param level Level pointer.
         */
	UIEngine(Snake* snake, Level* level);

	/**@brief Clears the terminal.
         */
	void clear_screen() const;

	/**@brief Prints given string.
         */
	void print(string s) const;

	/**@brief Prints Snaze's icon.
         */
	void icon() const;

	/**@brief Prints current game stats.
         */
	void stats() const;

	/**@brief Prints victory or defeat screen.
         */
	void victory_or_defeat() const;

private:
	/**@brief Stops program for given amount of miliseconds.
         */
	void wait(int ms) const;
};

#endif

