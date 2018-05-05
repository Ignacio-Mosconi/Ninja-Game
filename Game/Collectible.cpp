#include "Collectible.h"

Collectible::Collectible(int x, int y, const string& imagePath) : Entity(x, y, imagePath)
{
	disable();
	_flickeringCounter = 0;
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