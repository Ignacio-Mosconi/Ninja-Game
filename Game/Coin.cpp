#include "Coin.h"

Coin::Coin(int x, int y, const string& imagePath): Collectible (x, y, imagePath)
{
	_onScreenTime = COIN_DURATION;
	_spawnTime = rand() % (COIN_MAX_SPAWN_TIME - COIN_MIN_SPAWN_TIME) + COIN_MIN_SPAWN_TIME;
}

Coin::~Coin()
{
}

void Coin::update(float elapsed)
{
	if (_enabled)
	{
		_onScreenTime -= elapsed;
		if (_onScreenTime <= 0)
			disable();
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
	_sprite.setColor({ 255, 255, 255, 255 });
	_onScreenTime = COIN_DURATION;
	_spawnTime = rand() % (COIN_MAX_SPAWN_TIME - COIN_MIN_SPAWN_TIME) + COIN_MIN_SPAWN_TIME;
	_sprite.setPosition(rand() % (COLLECTIBLE_MAX_X - COLLECTIBLE_MIN_X - COIN_WIDTH) + COLLECTIBLE_MIN_X, 
		rand() % (COLLECTIBLE_MAX_Y - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y);
}