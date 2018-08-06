#include "ScoreMultiplier.h"
#include "State.h"

ScoreMultiplier::ScoreMultiplier(int x, int y, const string& imagePath) : Collectible(x, y, imagePath, 
rand() % (SCORE_MULT_MAX_SPAWN_TIME - SCORE_MULT_MIN_SPAWN_TIME) + SCORE_MULT_MIN_SPAWN_TIME, SCORE_MULT_DURATION)
{
	_sprite.setTextureRect(IntRect(_imagePosX, 0, SCORE_MULT_WIDTH, SCORE_MULT_HEIGHT));
}

ScoreMultiplier::~ScoreMultiplier()
{
}

void ScoreMultiplier::update(float elapsed)
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

void ScoreMultiplier::respawn()
{
	_enabled = true;
	_sprite.setColor(Color::White);
	_onScreenTime = SCORE_MULT_DURATION;
	_spawnTime = rand() % (SCORE_MULT_MAX_SPAWN_TIME - SCORE_MULT_MIN_SPAWN_TIME) + SCORE_MULT_MIN_SPAWN_TIME;
	_sprite.setPosition(rand() % (State::getScreenWidth() - COLLECTIBLE_SIDES_SPACE - SCORE_MULT_WIDTH) + COLLECTIBLE_SIDES_SPACE,
		rand() % (State::getScreenHeight() - State::getScreenHeight() * GROUND_POS_PERCENTAGE - SCORE_MULT_HEIGHT - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y);
}

void ScoreMultiplier::animate(float elapsed)
{
	_sprite.setTextureRect(IntRect(_imagePosX * SCORE_MULT_WIDTH, 0, SCORE_MULT_WIDTH, SCORE_MULT_HEIGHT));
	_animationCounter += elapsed;

	if (_animationCounter >= SCORE_MULT_FRAME_TIME)
	{
		_animationCounter = 0;
		if (_imagePosX < SCORE_MULT_MAX_INDEX)
			_imagePosX++;
		else
			_imagePosX = 0;
	}
}