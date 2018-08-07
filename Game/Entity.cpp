#include "Entity.h"
#include "State.h"

Entity::Entity(int x, int y, const string& imagePath)
{
	_texture.loadFromFile(imagePath);
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);

	Vector2f scaleFactors(State::getScaleFactors());
	_sprite.setScale(scaleFactors);
	_sprite.setPosition(x, y);
}