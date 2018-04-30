#include "Fruit.h"

Fruit::Fruit(int x, int y, const string& imagePath) : Entity(x, y, imagePath)
{
	_speed = rand() % (FRUIT_MAX_SPEED - FRUIT_MIN_SPEED) + FRUIT_MIN_SPEED;
}

Fruit::~Fruit()
{

}

void Fruit::update(float elapsed)
{
	if (_sprite.getPosition().y < SCREEN_HEIGHT - GROUND_HEIGHT)
	{
		_sprite.move(0, _speed * elapsed);
		_speed += FRUIT_MIN_SPEED;
	}
	else
		respawn();
}

void Fruit::respawn()
{
	_sprite.setPosition(rand() % (FRUIT_MAX_X - FRUIT_MIN_X) + FRUIT_MIN_X, FRUIT_MIN_Y);
	_speed = rand() % (FRUIT_MAX_SPEED - FRUIT_MIN_SPEED) + FRUIT_MIN_SPEED;
}