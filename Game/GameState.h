#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Player.h"
#include "Fruit.h"
#include "Coin.h"
#include "Life.h"
#include "TimeBonus.h"
#include "HUD.h"
using namespace sf;

class GameState : public State
{
private:
	Player* _player;
	Fruit* _fruits[FRUITS];
	Coin* _coins[COINS];
	Life* _life;
	TimeBonus* _timeBonus;

	Entity* _ground;
	Entity* _sky;

	HUD* _hud;

	Music _mainTheme;

	bool _gameOver;
	bool _paused;
	int _score;
	int _highestScore;
	float _time;
	float _timeSinceLastFrame;

	void fruitPlayerCollision(Fruit* f, Player* p);
	void coinPlayerCollision(Coin* c, Player* p);
	void lifePlayerCollision(Life* l, Player* p);
	void timeBonusPlayerCollision(TimeBonus* t, Player* p);

	void result();

	void run();

protected:
	void input();
	void update(float elapsed);
	void draw();

	void pause();
	void resume();

public:
	GameState(RenderWindow& window);
	~GameState();

	void restart();

	inline bool gameOver() { return _gameOver; }
};

#endif
