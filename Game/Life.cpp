#include "Life.h"

Life::Life(int x, int y, const string& imagePath) : Collectible(x, y, imagePath)
{
	_onScreenTime = COIN_DURATION;
	_spawnTime = rand() % (LIFE_MAX_SPAWN_TIME - LIFE_MIN_SPAWN_TIME) + LIFE_MIN_SPAWN_TIME;
	_sprite.setTextureRect(IntRect(_imagePosX, 0, LIFE_WIDTH, LIFE_HEIGHT));
}

Life::~Life()
{
}

void Life::update(float elapsed)
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

void Life::respawn()
{
	_enabled = true;
	_sprite.setColor(Color::White);
	_onScreenTime = LIFE_DURATION;
	_spawnTime = rand() % (LIFE_MAX_SPAWN_TIME - LIFE_MIN_SPAWN_TIME) + LIFE_MIN_SPAWN_TIME;
	_sprite.setPosition(rand() % (COLLECTIBLE_MAX_X - COLLECTIBLE_MIN_X - LIFE_WIDTH) + COLLECTIBLE_MIN_X,
		rand() % (COLLECTIBLE_MAX_Y - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y);
}

void Life::animate(float elapsed)
{
	_sprite.setTextureRect(IntRect(_imagePosX * LIFE_WIDTH, 0, LIFE_WIDTH, LIFE_HEIGHT));
	_animationCounter += elapsed;

	if (_animationCounter >= LIFE_FRAME_TIME)
	{
		_animationCounter = 0;
		if (_imagePosX < LIFE_MAX_INDEX)
			_imagePosX++;
		else
			_imagePosX = 0;
	}
}