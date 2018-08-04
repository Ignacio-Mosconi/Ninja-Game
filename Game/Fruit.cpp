#include "Fruit.h"

float Fruit::_gameTime = 0;

Fruit::Fruit(int x, int y, const string& imagePath) : Entity(x, y, imagePath),
_speed(rand() % (FRUIT_MAX_SPEED - FRUIT_MIN_SPEED) + FRUIT_MIN_SPEED), _rotationSpeed(_speed),
_spawnTime(rand() % (FRUIT_MAX_SPAWN_TIME - FRUIT_MIN_SPAWN_TIME) + FRUIT_MIN_SPAWN_TIME),
_kind(chooseKind()), _hasReachedBottom(false)
{
	_crashBuffer.loadFromFile(FRUIT_CRASH_SOUND);
	_crash.setBuffer(_crashBuffer);
	_sprite.setTextureRect(IntRect(_kind * FRUIT_WIDTH, 0, FRUIT_WIDTH, FRUIT_HEIGHT));
	
	disable();
}

Fruit::~Fruit()
{
}

void Fruit::update(float elapsed)
{
	if (_enabled)
	{
		if (_sprite.getPosition().y < SCREEN_HEIGHT - GROUND_HEIGHT)
			move(elapsed);
		else
		{
			_crash.play();
			_hasReachedBottom = true;;
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

void Fruit::move(float elapsed)
{
	_sprite.move(0, _speed * elapsed);
	_sprite.rotate(_rotationSpeed * elapsed);
	_speed += 2;
	_rotationSpeed = _speed / 5;
}

void Fruit::disable()
{
	_enabled = false;
	_sprite.setColor(Color::Transparent);
}

void Fruit::respawn()
{
	_enabled = true;
	_sprite.setColor(Color::White);
	_sprite.setPosition(rand() % (FRUIT_MAX_X - FRUIT_MIN_X - FRUIT_WIDTH) + FRUIT_MIN_X, FRUIT_MIN_Y);
	_speed = rand() % (FRUIT_MAX_SPEED - FRUIT_MIN_SPEED) + FRUIT_MIN_SPEED * (_gameTime / 2);
	_rotationSpeed = _speed / 5;
	_spawnTime = rand() % (FRUIT_MAX_SPAWN_TIME - FRUIT_MIN_SPAWN_TIME) + FRUIT_MIN_SPAWN_TIME;
	_kind = chooseKind();
	_sprite.setTextureRect(IntRect(_kind * FRUIT_WIDTH, 0, FRUIT_WIDTH, FRUIT_HEIGHT));
}

Kind Fruit::chooseKind()
{
	switch (rand() % (FRUIT_MAX_INDEX + 1))
	{
		case 0:
			return Watermelon;
			break;
		case 1:
			return Apple;
			break;
		case 2:
			return Pear;
			break;
		case 3:
			return Banana;
			break;
		default:
			return Watermelon;
	}
}