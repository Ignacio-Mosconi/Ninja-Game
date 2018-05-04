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