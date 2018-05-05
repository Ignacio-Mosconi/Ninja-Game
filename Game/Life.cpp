#include "Life.h"

Life::Life(int x, int y, const string& imagePath) : Collectible(x, y, imagePath)
{
	_onScreenTime = COIN_DURATION;
	_spawnTime = rand() % (LIFE_MAX_SPAWN_TIME - LIFE_MIN_SPAWN_TIME) + LIFE_MIN_SPAWN_TIME;
}

Life::~Life()
{
}

void Life::update(float elapsed)
{
	if (_enabled)
	{
		_onScreenTime -= elapsed;
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

void Life::respawn()
{
	_enabled = true;
	_sprite.setColor(Color::White);
	_onScreenTime = LIFE_DURATION;
	_spawnTime = rand() % (LIFE_MAX_SPAWN_TIME - LIFE_MIN_SPAWN_TIME) + LIFE_MIN_SPAWN_TIME;
	_sprite.setPosition(rand() % (COLLECTIBLE_MAX_X - COLLECTIBLE_MIN_X - LIFE_WIDTH) + COLLECTIBLE_MIN_X,
		rand() % (COLLECTIBLE_MAX_Y - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y);
}