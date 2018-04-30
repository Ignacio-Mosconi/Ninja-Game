#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Player.h"
#include "Fruit.h"
#include "HUD.h"
using namespace sf;

class GameState : public State
{
private:
	Player* _player;
	Fruit* _fruits[FRUITS];
	Entity* _ground;

	HUD* _hud;

	bool _gameOver;
	bool _paused;

	const float _drawFrameTime = 1.0f / 60.0f;
	float _deltaTime;

	void fruitPlayerCollision(Fruit* fruit, Player* p);

protected:
	void input();
	void update(float elapsed);
	void draw(float elapsed);

	void pause();
	void resume();

public:
	GameState(RenderWindow& window);
	~GameState();

	void run();
};

#endif
