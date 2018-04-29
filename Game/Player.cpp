#include "Player.h"

Player::Player(int x, int y, const string& imagePath) : Entity(x, y, imagePath)
{
	_currentState = Idle;
	_moveSpeed = PLAYER_MOVE_SPEED;
	_jumpSpeed = PLAYER_JUMP_SPEED;
}

Player::~Player()
{

}

void Player::update(float elapsed)
{
	switch (_currentState)
	{
		case Idle:
			move(elapsed);
			jump(elapsed);
			break;
		case Moving:
			move(elapsed);
			jump(elapsed);
			break;
		case Jumping:
			fall(elapsed);
		case Falling:
			fall(elapsed);
			break;
	}
}

void Player::move(float elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::Left) && _sprite.getPosition().x > 0)
	{
		_sprite.move(-_moveSpeed * elapsed, 0);
		_currentState = Moving;
	}
	else
		if (Keyboard::isKeyPressed(Keyboard::Right) && _sprite.getPosition().x < SCREEN_WIDTH - PLAYER_WIDTH)
		{
			_sprite.move(_moveSpeed * elapsed, 0);
			_currentState = Moving;
		}
}

void Player::jump(float elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		_sprite.move(0, _jumpSpeed * elapsed);
		_currentState = Jumping;
	}
}

void Player::fall(float elapsed)
{
	if (_sprite.getPosition().y + PLAYER_HEIGHT < SCREEN_HEIGHT - GROUND_HEIGHT)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left) && _sprite.getPosition().x > 0)
			_sprite.move(-_moveSpeed * elapsed, GRAVITY * elapsed);
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Right) && _sprite.getPosition().x < SCREEN_WIDTH - PLAYER_WIDTH)
				_sprite.move(_moveSpeed * elapsed, GRAVITY * elapsed);
			else
				_sprite.move(0, GRAVITY * elapsed);

			_currentState = Falling;
		}
	}
	else
	{
		_currentState = Idle;
	}
}