#include "Coin.h"
#include "State.h"
#include "GameState.h"

Coin::Coin(int x, int y, const string& imagePath) : 
Collectible(x, y, imagePath, rand() % (COIN_MAX_SPAWN_TIME - COIN_MIN_SPAWN_TIME) + COIN_MIN_SPAWN_TIME, COIN_DURATION)
{
	_sprite.setTextureRect(IntRect(_imagePosX, 0, COIN_WIDTH, COIN_HEIGHT));
}

Coin::~Coin()
{
}

void Coin::update(float elapsed)
{
	if (_enabled)
	{
		_onScreenTime -= elapsed;
		animate(elapsed);
		if (_onScreenTime <= COLLECTIBLE_START_FLICKERING)
		{
			flicker(elapsed);
			if (_onScreenTime <= 0)
				disable();
		}
	}
	else
	{
		_spawnTime -= elapsed;
		if (_spawnTime <= 0)
			respawn();
	}
}

void Coin::respawn()
{
	_enabled = true;
	_sprite.setColor(Color::White);
	_onScreenTime = COIN_DURATION;
	_spawnTime = rand() % (COIN_MAX_SPAWN_TIME - COIN_MIN_SPAWN_TIME) + COIN_MIN_SPAWN_TIME;
	_sprite.setPosition(rand() % (State::getScreenWidth() - COLLECTIBLE_SIDES_SPACE - COIN_WIDTH) + COLLECTIBLE_SIDES_SPACE, 
		rand() % (State::getScreenHeight() - GameState::getGroundHeight() - COIN_HEIGHT - _minY) + _minY);
}

void Coin::animate(float elapsed)
{
	_sprite.setTextureRect(IntRect(_imagePosX * COIN_WIDTH, 0, COIN_WIDTH, COIN_HEIGHT));
	_animationCounter += elapsed;

	if (_animationCounter >= COIN_FRAME_TIME)
	{
		_animationCounter = 0;
		if (_imagePosX < COIN_MAX_INDEX)
			_imagePosX++;
		else
			_imagePosX = 0;
	}
}