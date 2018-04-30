#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Player.h"
#include "Fruit.h"
using namespace sf;

class GameState : public State
{
private:
	Player* _player;
	Fruit* _fruits[FRUITS];
	bool gameOver;

protected:
	void input();
	void update(float elapsed);
	void draw(float elapsed);

public:
	GameState(RenderWindow& window);
	~GameState();

	void run();
};

#endif
