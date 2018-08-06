#include "Entity.h"
#include "State.h"

Entity::Entity(int x, int y, const string& imagePath)
{
	_texture.loadFromFile(imagePath);
	_sprite.setTexture(_texture);
	
	Vector2f scaleFactors((float)State::getScreenWidth() / DEFAULT_WIDTH , (float)State::getScreenHeight() / DEFAULT_HEIGHT);
	_sprite.setScale(scaleFactors);
	_sprite.setPosition(x, y);
}