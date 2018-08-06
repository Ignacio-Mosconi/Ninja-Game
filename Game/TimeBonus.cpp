#include "TimeBonus.h"
#include "State.h"
#include "GameState.h"

TimeBonus::TimeBonus(int x, int y, const string& imagePath) :
Collectible(x, y, imagePath, rand() % (TIME_BONUS_MAX_SPAWN_TIME - TIME_BONUS_MIN_SPAWN_TIME) + TIME_BONUS_MIN_SPAWN_TIME,
			TIME_BONUS_DURATION)
{
	_sprite.setTextureRect(IntRect(_imagePosX, 0, TIME_BONUS_WIDTH, TIME_BONUS_HEIGHT));
}

TimeBonus::~TimeBonus()
{
}

void TimeBonus::update(float elapsed)
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

void TimeBonus::respawn()
{
	_enabled = true;
	_sprite.setColor(Color::White);
	_onScreenTime = TIME_BONUS_DURATION;
	_spawnTime = rand() % (TIME_BONUS_MAX_SPAWN_TIME - TIME_BONUS_MIN_SPAWN_TIME) + TIME_BONUS_MIN_SPAWN_TIME;
	_sprite.setPosition(rand() % (State::getScreenWidth() - COLLECTIBLE_SIDES_SPACE - TIME_BONUS_WIDTH) + COLLECTIBLE_SIDES_SPACE, 
		rand() % (State::getScreenHeight() - GameState::getGroundHeight() - TIME_BONUS_HEIGHT - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y);
}

void TimeBonus::animate(float elapsed)
{
	_sprite.setTextureRect(IntRect(_imagePosX * TIME_BONUS_WIDTH, 0, TIME_BONUS_WIDTH, TIME_BONUS_HEIGHT));
	_animationCounter += elapsed;

	if (_animationCounter >= TIME_BONUS_FRAME_TIME)
	{
		_animationCounter = 0;
		if (_imagePosX < TIME_BONUS_MAX_INDEX)
			_imagePosX++;
		else
			_imagePosX = 0;
	}
}