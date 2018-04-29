#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "State.h"
using namespace sf;

class GameState : public State
{
private:
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
