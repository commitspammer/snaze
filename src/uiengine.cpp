#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include "uiengine.h"
#include "snake.h"
#include "level.h"

using namespace std;

UIEngine::UIEngine(Snake* snake, Level* level)
{
	this->snake = snake;
	this->level = level;
}

void UIEngine::wait(int ms) const
{
	this_thread::sleep_for(chrono::milliseconds(ms));
}

void UIEngine::clear_screen() const
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined (__gnu_linux__) || defined (__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

void UIEngine::print(string s) const
{
	cout << s;
}

void UIEngine::icon() const
{
	cout << endl;
	for (int i = 0; i < 25; i++) cout << "=";
	cout << endl;
	cout << " ___ _ __   __ _ _______" << endl;
	cout << "/ __| '_ \\ / _` |_  / _ \\" << endl;
	cout << "\\__ \\ | | | (_| |/ /  __/" << endl;
	cout << "|___/_| |_|\\__,_/___\\___|" << endl;
	for (int i = 0; i < 25; i++) cout << "=";
	cout << endl;
}

void UIEngine::stats() const
{
	cout.fill('0');
	cout << endl;
	for (int i = 0; i < 30; i++) cout << "=";
	cout << endl;
	cout << "Vidas: " << setw(2) << this->snake->get_lifes();
	for (int i = 0; i < 10; i++) cout << " ";
	cout << "Comidas: " << setw(2)
	     << this->level->get_food_count() - this->snake->get_food_eaten() << endl;
	for (int i = 0; i < 9; i++) cout << " ";
	cout << "Score: " << setw(3) << this->snake->get_score() << endl;
	for (int i = 0; i < 30; i++) cout << "=";
	cout << endl;
}

void UIEngine::victory_or_defeat() const
{
	if (this->snake->get_lifes() == 0) {
		cout << endl;
		for (int i = 0; i < 30; i++) cout << "=";
		cout << endl;
		cout << "Derrota!! Suas vidas acabaram." << endl;
		for (int i = 0; i < 30; i++) cout << "=";
		cout << endl;
	} else {
		cout << endl;
		for (int i = 0; i < 22; i++) cout << "=";
		cout << endl;
		cout << "Vitoria!! Você passou." << endl;
		for (int i = 0; i < 22; i++) cout << "=";
		cout << endl;
	}
}
