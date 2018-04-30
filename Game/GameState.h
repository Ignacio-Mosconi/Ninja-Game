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
	Entity* _ground;
	bool _gameOver;

	const float _drawFrameTime = 1.0f / 60.0f;
	float _deltaTime;

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
