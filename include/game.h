#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>
#include "snake.h"
#include "level.h"
#include "ai.h"
#include "uiengine.h"

using namespace std;

class Game {
public:
	/**@brief Different game states. */
	enum GameState {
	    INTRO,
	    RUNNING,
	    GAME_OVER,
	};

private:
	/**@brief Pointer for the snake. */
	Snake* snake;

	/**@brief Pointer for the level. */
	Level* level;

	/**@brief Pointer for the AI. */
	AI* ai;

	/**@brief User interface generator. */
	UIEngine ui;

	/**@brief Current state. */
	GameState state;

	/**@brief "pacman" or "snake" gamemode. */
	string mode;

	/**@brief AI's move input. */
	Snake::Direction ai_input;

	/**@brief Frames rendered. */
	int frame_count;

public:
	/**@brief Game constructor.
	 * @param mode Gamemode.
	 * @param snake Snake pointer.
	 * @param level Level pointer
	 * @param ai AI pointer.
	 */
	Game(string mode, Snake* snake, Level* level, AI* ai);

	/**@brief Starts the game.
	 */
	void start();

private:
	/**@brief Reads move from AI. Stores it in ai_input.
	 */
	void get_input();

	/**@brief Updates the whole state of the game.
	 */
	void update();

	/**@brief Prints the game interface.
	 */
	void render();
};

#endif

