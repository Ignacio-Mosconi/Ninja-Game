#include "Player.h"

Player::Player(int x, int y, const string& imagePath) : Entity(x, y, imagePath)
{
	_jumpBuffer.loadFromFile(JUMP_SOUND);
	_fruitHitBuffer.loadFromFile(FRUIT_HIT_SOUND);
	_pickUpCoinBuffer.loadFromFile(PICK_UP_COIN_SOUND);
	_pickUpLifeBuffer.loadFromFile(PICK_UP_LIFE_SOUND);

	_jump.setBuffer(_jumpBuffer);
	_fruitHit.setBuffer(_fruitHitBuffer);
	_pickUpCoin.setBuffer(_pickUpCoinBuffer);
	_pickUpLife.setBuffer(_pickUpLifeBuffer);

	_currentState = Idle;
	_facing = Right;
	_animationCounter = 0;
	_imagePos.x = 0;
	_imagePos.y = IdleRight;
	_sprite.setTextureRect(IntRect(_imagePos.x, _imagePos.y, PLAYER_WIDTH, PLAYER_HEIGHT));

	_lives = PLAYER_LIVES;
	_moveSpeed = PLAYER_MOVE_SPEED;
	_jumpSpeed = PLAYER_JUMP_SPEED;
	_isInvincible = false;
	_flickeringTime = FLICKERING_TIME;
	_flickeringCounter = 0;
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
			jump(elapsed);
			break;
		case Falling:
			fall(elapsed);
			break;
	}
	
	if (_isInvincible)
		flicker(elapsed);
	
	animate(elapsed);
}

void Player::move(float elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::Left) && _sprite.getPosition().x > 0)
	{
		_sprite.move(-_moveSpeed * elapsed, 0);
		if (_facing == Right)
		{
			//_sprite.setTextureRect(IntRect(PLAYER_WIDTH, PLAYER_HEIGHT, -PLAYER_WIDTH, 2 * PLAYER_HEIGHT));
			_imagePos.x = 0;
			_imagePos.y = MovingLeft;
			_facing = Left;
		}
		if (_currentState != Moving)
		{
			_imagePos.x = 0;
			_imagePos.y = MovingLeft;
			_currentState = Moving;
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Right) && _sprite.getPosition().x < SCREEN_WIDTH - PLAYER_WIDTH)
		{
			_sprite.move(_moveSpeed * elapsed, 0);
			if (_facing == Left)
			{
				//_sprite.setTextureRect(IntRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, 2 * PLAYER_HEIGHT));
				_imagePos.x = 0;
				_imagePos.y = MovingRight;
				_facing = Right;
			}
			if (_currentState != Moving)
			{
				_imagePos.x = 0;
				_imagePos.y = MovingRight;
				_currentState = Moving;
			}
		}
		else
			if (_currentState != Idle)
			{
				_imagePos.x = 0;
				_imagePos.y = (_facing == Right) ? IdleRight : IdleLeft;
				_currentState = Idle;
			}
	}
}

void Player::jump(float elapsed)
{
	if (Keyboard::isKeyPressed(Keyboard::S) && _currentState != Jumping)
	{
		_jump.play();
		_sprite.move(0, _jumpSpeed * elapsed);
		_imagePos.x = 0;
		_imagePos.y = (_facing == Right) ? JumpingRight : JumpingLeft;
		_currentState = Jumping;
	}
	else
	{
		if (_currentState == Jumping)
		{
			if (_sprite.getPosition().y > SCREEN_HEIGHT - PLAYER_JUMP_HEIGHT - GROUND_HEIGHT)
			{
				if (Keyboard::isKeyPressed(Keyboard::Left) && _sprite.getPosition().x > 0)
				{
					_sprite.move(-_moveSpeed * elapsed, _jumpSpeed * elapsed);
					if (_facing == Right)
					{
						//_sprite.setTextureRect(IntRect(PLAYER_WIDTH, PLAYER_HEIGHT, -PLAYER_WIDTH, 2 * PLAYER_HEIGHT));
						_imagePos.y = JumpingLeft;
						_facing = Left;
					}
				}
				else
				{
					if (Keyboard::isKeyPressed(Keyboard::Right) && _sprite.getPosition().x < SCREEN_WIDTH - PLAYER_WIDTH)
					{
						_sprite.move(_moveSpeed * elapsed, _jumpSpeed * elapsed);
						if (_facing == Left)
						{
							//_sprite.setTextureRect(IntRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, 2 * PLAYER_HEIGHT));
							_imagePos.y = JumpingRight;
							_facing = Right;
						}
					}
					else
						_sprite.move(0, _jumpSpeed * elapsed);
				}
			}
			else
				_currentState = Falling;
		}
	}
}

void Player::fall(float elapsed)
{
	if (_sprite.getPosition().y + PLAYER_HEIGHT < SCREEN_HEIGHT - GROUND_HEIGHT)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left) && _sprite.getPosition().x > 0)
		{
			_sprite.move(-_moveSpeed * elapsed, GRAVITY * elapsed);
			if (_facing == Right)
			{
				//_sprite.setTextureRect(IntRect(PLAYER_WIDTH, PLAYER_HEIGHT, -PLAYER_WIDTH, 2 * PLAYER_HEIGHT));
				_imagePos.y = JumpingLeft;
				_facing = Left;
			}
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Right) && _sprite.getPosition().x < SCREEN_WIDTH - PLAYER_WIDTH)
			{
				_sprite.move(_moveSpeed * elapsed, GRAVITY * elapsed);
				if (_facing == Left)
				{
					//_sprite.setTextureRect(IntRect(0, PLAYER_HEIGHT, PLAYER_WIDTH, 2 * PLAYER_HEIGHT));
					_imagePos.y = JumpingRight;
					_facing = Right;
				}
			}
			else
				_sprite.move(0, GRAVITY * elapsed);
		}
	}
	else
	{
		_sprite.setPosition(_sprite.getPosition().x, SCREEN_HEIGHT - GROUND_HEIGHT - PLAYER_HEIGHT);
		_imagePos.x = 0;
		_imagePos.y = (_facing == Right) ? IdleRight : IdleLeft;
		_currentState = Idle;
	}
}

bool Player::pickUpItem(Collectables collectable)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		switch (collectable)
		{
			case Coins:
				_pickUpCoin.play();
				break;
			case LifeBonuses:
				_pickUpLife.play();
				_lives++;
				break;
		}
		return true;
	}
	return false;
}

void Player::die()
{
	_fruitHit.play();
	_isInvincible = true;
	_lives--;
	respawn();
}

void Player::respawn()
{
	_currentState = Idle;
	_sprite.setPosition(SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, SCREEN_HEIGHT - GROUND_HEIGHT - PLAYER_HEIGHT);
}

void Player::flicker(float elapsed)
{
	_flickeringCounter += elapsed;
	if (_flickeringCounter >= FLICKERING_RATE)
	{
		_flickeringCounter = 0;
		if (_sprite.getColor() != Color::Transparent)
			_sprite.setColor(Color::Transparent);
		else
			_sprite.setColor(Color::White);
	}
	else
		_flickeringCounter += elapsed;

	_flickeringTime -= elapsed;
	if (_flickeringTime <= 0)
	{
		_isInvincible = false;
		_sprite.setColor(Color::White);
		_flickeringTime = FLICKERING_TIME;
	}
}

void Player::animate(float elapsed)
{
	_sprite.setTextureRect(IntRect(_imagePos.x * PLAYER_WIDTH, _imagePos.y * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
	_animationCounter += elapsed;

	switch (_currentState)
	{
		case Idle:
			if (_animationCounter >= IDLE_FRAME_TIME)
			{
				_animationCounter = 0;
				if (_imagePos.x < IMAGE_MAX_INDEX)
					_imagePos.x++;
				else
					_imagePos.x = 0;
			}
			break;
		case Moving:
			if (_animationCounter >= MOVING_FRAME_TIME)
			{
				_animationCounter = 0;
				if (_imagePos.x < IMAGE_MAX_INDEX)
					_imagePos.x++;
				else
					_imagePos.x = 0;
			}
			break;
		case Jumping:
			if (_animationCounter >= 1.0f / 18.0f)
			{
				_animationCounter = 0;
				if (_imagePos.x < 2)
					_imagePos.x++;
			}
			break;
	}
}
