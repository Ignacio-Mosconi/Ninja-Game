#include "Collectible.h"

Collectible::Collectible(int x, int y, const string& imagePath) : Entity(x, y, imagePath)
{
	disable();
}

void Collectible::disable()
{
	_enabled = false;
	_sprite.setColor({ 0, 0, 0, 0 });
}