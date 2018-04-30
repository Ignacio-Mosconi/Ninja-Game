#include "Fruit.h"

Fruit::Fruit(int x, int y, const string& imagePath) : Entity(x, y, imagePath)
{
	_speed = rand() % (FRUIT_MAX_SPEED - FRUIT_MIN_SPEED) + FRUIT_MIN_SPEED;
	_spawnTime = rand() % (FRUIT_MAX_SPAWN_TIME - FRUIT_MIN_SPAWN_TIME) + FRUIT_MIN_SPAWN_TIME;
	
	disable();
}

Fruit::~Fruit()
{

}

void Fruit::update(float elapsed)
{
	if (_active)
	{
		if (_sprite.getPosition().y < SCREEN_HEIGHT - GROUND_HEIGHT)
			move(elapsed);
		else
			disable();
	}
	else
	{
		_spawnTime -= elapsed;
		if (_spawnTime <= 0)
			respawn();
	}
}

void Fruit::move(float elapsed)
{
	_sprite.move(0, _speed * elapsed);
	_speed += FRUIT_MIN_SPEED;
}

void Fruit::disable()
{
	_active = false;
	_sprite.setColor({ 0, 0, 0, 0 });
}

void Fruit::respawn()
{
	_active = true;
	_spawnTime = rand() % (FRUIT_MAX_SPAWN_TIME - FRUIT_MIN_SPAWN_TIME) + FRUIT_MIN_SPAWN_TIME;
	_sprite.setColor({ 255, 255, 255, 255 });
	_sprite.setPosition(rand() % (FRUIT_MAX_X - FRUIT_MIN_X) + FRUIT_MIN_X, FRUIT_MIN_Y);
	_speed = rand() % (FRUIT_MAX_SPEED - FRUIT_MIN_SPEED) + FRUIT_MIN_SPEED;
}