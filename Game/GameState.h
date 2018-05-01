#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Player.h"
#include "Fruit.h"
#include "Coin.h"
#include "Life.h"
#include "HUD.h"
using namespace sf;

class GameState : public State
{
private:
	Player* _player;
	Fruit* _fruits[FRUITS];
	Entity* _ground;
	Coin* _coins[COINS];
	Life* _life;

	HUD* _hud;

	bool _gameOver;
	bool _paused;
	int _score;
	int _highestScore;

	const float _drawFrameTime = 1.0f / 60.0f;
	float _deltaTime;

	void fruitPlayerCollision(Fruit* f, Player* p);
	void coinPlayerCollision(Coin* c, Player* p);
	void lifePlayerCollision(Life* l, Player* p);

	void result();

	void run();

protected:
	void input();
	void update(float elapsed);
	void draw(float elapsed);

	void pause();
	void resume();

public:
	GameState(RenderWindow& window);
	~GameState();

	void restart();

	inline bool gameOver() { return _gameOver; }
};

#endif
