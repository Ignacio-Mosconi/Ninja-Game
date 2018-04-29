#include "Entity.h"

Entity::Entity(int x, int y, const string& imagePath)
{
	_texture.loadFromFile(imagePath);
	_sprite.setTexture(_texture);
	_sprite.setPosition(x, y);
}