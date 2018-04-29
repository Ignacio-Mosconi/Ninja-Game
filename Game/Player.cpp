#include "Player.h"

Player::Player(int x, int y, const string& imagePath) : Entity(x, y, imagePath)
{
	_speed = PLAYER_SPEED;
}

Player::~Player()
{

}

void Player::update(float elapsed)
{
	move(elapsed);
}

void Player::move(float elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
		_sprite.move(-_speed, 0);
	else
		if (Keyboard::isKeyPressed(Keyboard::Right))
			_sprite.move(_speed * elapsed, 0);
}

void Player::jump()
{

}