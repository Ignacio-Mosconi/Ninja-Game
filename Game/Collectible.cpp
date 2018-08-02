#include "Collectible.h"

Collectible::Collectible(int x, int y, const string& imagePath, float spawnTime, float onScreenTime) : Entity(x, y, imagePath),
_spawnTime(spawnTime), _onScreenTime(onScreenTime), _flickeringCounter(0), _imagePosX(0), _animationCounter(0)
{
	disable();
}

void Collectible::disable()
{
	_enabled = false;
	_sprite.setColor(Color::Transparent);
}

void Collectible::flicker(float elapsed)
{
	_flickeringCounter += elapsed;
	if (_flickeringCounter >= FLICKERING_RATE)
	{
		_flickeringCounter = 0;
		if (_sprite.getColor() != Color::Transparent)
			_sprite.setColor(Color::Transparent);
		else
			_sprite.setColor(Color::White);
	}
	else
		_flickeringCounter += elapsed;
}