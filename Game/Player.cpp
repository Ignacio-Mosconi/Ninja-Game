#include "Player.h"
#include "State.h"
#include "GameState.h"

Player::Player(int x, int y, const string& imagePath) : Entity(x, y, imagePath),
_currentState(Idle), _facing(Right), _animationCounter(0), _imagePos(0, IdleRight), _lives(PLAYER_LIVES),
_moveSpeed(PLAYER_MOVE_SPEED), _jumpSpeed(PLAYER_JUMP_SPEED), _jumpHeight(State::getScreenHeight() * PLAYER_JUMP_HEIGHT_PERCENTAGE),
_isInvincible(false), _flickeringTime(FLICKERING_TIME), _flickeringCounter(0), _hasCollectedItem(false), _pickUpCooldown(0)
{
	_jumpBuffer.loadFromFile(JUMP_SOUND);
	_fruitHitBuffer.loadFromFile(FRUIT_HIT_SOUND);
	_pickUpCoinBuffer.loadFromFile(PICK_UP_COIN_SOUND);
	_pickUpLifeBuffer.loadFromFile(PICK_UP_LIFE_SOUND);
	_pickUpTimeBonusBuffer.loadFromFile(PICK_UP_TIME_BONUS_SOUND);
	_pickUpScoreMultBuffer.loadFromFile(PICK_UP_SCORE_MULT_SOUND);
	_gameOverBuffer.loadFromFile(GAME_OVER_SOUND);

	_jump.setBuffer(_jumpBuffer);
	_fruitHit.setBuffer(_fruitHitBuffer);
	_pickUpCoin.setBuffer(_pickUpCoinBuffer);
	_pickUpLife.setBuffer(_pickUpLifeBuffer);
	_pickUpTimeBonus.setBuffer(_pickUpTimeBonusBuffer);
	_pickUpScoreMult.setBuffer(_pickUpScoreMultBuffer);
	_gameOver.setBuffer(_gameOverBuffer);

	_sprite.setTextureRect(IntRect(_imagePos.x, _imagePos.y, PLAYER_WIDTH, PLAYER_HEIGHT));
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
	
	if (_hasCollectedItem)
	{
		_pickUpCooldown += elapsed;
		if (_pickUpCooldown >= PICK_UP_COOLDOWN)
		{
			_pickUpCooldown = 0;
			_hasCollectedItem = false;
		}
	}

	if (_isInvincible)
		flicker(elapsed);
	
	animate(elapsed);
}

void Player::move(float elapsed)
{
	if ((Keyboard::isKeyPressed(Keyboard::Left) || Joystick::getAxisPosition(0, Joystick::PovX) < 0 || 
		Joystick::getAxisPosition(0, Joystick::X) < -STICK_SENSITIVITY) 
		&& _sprite.getPosition().x > 0)
	{
		_sprite.move(-_moveSpeed * elapsed, 0);
		if (_facing == Right)
		{
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
		if ((Keyboard::isKeyPressed(Keyboard::Right) || Joystick::getAxisPosition(0, Joystick::PovX) > 0 ||
			Joystick::getAxisPosition(0, Joystick::X) > STICK_SENSITIVITY) &&
			_sprite.getPosition().x < State::getScreenWidth() - PLAYER_WIDTH * State::getScaleFactors().x)
		{
			_sprite.move(_moveSpeed * elapsed, 0);
			if (_facing == Left)
			{
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
	if ((Keyboard::isKeyPressed(Keyboard::JUMP_KEY) || Joystick::isButtonPressed(0, JUMP_BUTTON)) 
		&& _currentState != Jumping)
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
			if (_sprite.getPosition().y > State::getScreenHeight() - _jumpHeight - GameState::getGroundHeight())
			{
				if ((Keyboard::isKeyPressed(Keyboard::Left) || Joystick::getAxisPosition(0, Joystick::PovX) < 0 ||
					Joystick::getAxisPosition(0, Joystick::X) < -STICK_SENSITIVITY) && _sprite.getPosition().x > 0)
				{
					_sprite.move(-_moveSpeed * elapsed, _jumpSpeed * elapsed);
					if (_facing == Right)
					{
						_imagePos.y = JumpingLeft;
						_facing = Left;
					}
				}
				else
				{
					if ((Keyboard::isKeyPressed(Keyboard::Right) || Joystick::getAxisPosition(0, Joystick::PovX) > 0 ||
						Joystick::getAxisPosition(0, Joystick::X) > STICK_SENSITIVITY) &&
						_sprite.getPosition().x < State::getScreenWidth() - PLAYER_WIDTH * State::getScaleFactors().x)
					{
						_sprite.move(_moveSpeed * elapsed, _jumpSpeed * elapsed);
						if (_facing == Left)
						{
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
	if (_sprite.getPosition().y + PLAYER_HEIGHT * State::getScaleFactors().y < State::getScreenHeight() - GameState::getGroundHeight())
	{
		if ((Keyboard::isKeyPressed(Keyboard::Left) || Joystick::getAxisPosition(0, Joystick::PovX) < 0 ||
			Joystick::getAxisPosition(0, Joystick::X) < -STICK_SENSITIVITY) && _sprite.getPosition().x > 0)
		{
			_sprite.move(-_moveSpeed * elapsed, GRAVITY * elapsed);
			if (_facing == Right)
			{
				_imagePos.y = JumpingLeft;
				_facing = Left;
			}
		}
		else
		{
			if ((Keyboard::isKeyPressed(Keyboard::Right) || Joystick::getAxisPosition(0, Joystick::PovX) > 0 ||
				Joystick::getAxisPosition(0, Joystick::X) > STICK_SENSITIVITY) &&
				_sprite.getPosition().x < State::getScreenWidth() - PLAYER_WIDTH * State::getScaleFactors().x)
			{
				_sprite.move(_moveSpeed * elapsed, GRAVITY * elapsed);
				if (_facing == Left)
				{
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
		_sprite.setPosition(_sprite.getPosition().x,
			State::getScreenHeight() - GameState::getGroundHeight() - PLAYER_HEIGHT * State::getScaleFactors().y);
		_imagePos.x = 0;
		_imagePos.y = (_facing == Right) ? IdleRight : IdleLeft;
		_currentState = Idle;
	}
}

bool Player::pickUpItem(Collectables collectable)
{
	if (Keyboard::isKeyPressed(Keyboard::COLLECT_KEY) || Joystick::isButtonPressed(0, COLLECT_BUTTON) && !_hasCollectedItem)
		switch (collectable)
		{
			case Coins:
				_pickUpCoin.play();
				_hasCollectedItem = true;
				return true;
			case LifeBonuses:
				_pickUpLife.play();
				_lives++;
				_hasCollectedItem = true;
				return true;
			case TimeBonuses:
				_pickUpTimeBonus.play();
				_hasCollectedItem = true;
				return true;
			case ScoreMultipliers:
				_pickUpScoreMult.play();
				_hasCollectedItem = true;
				return true;
		}
	return false;
}

void Player::die()
{
	_fruitHit.play();
	_isInvincible = true;
	_lives--;
	if (_lives == 0)
		_gameOver.play();
	else
		respawn();
}

void Player::respawn()
{
	_currentState = Idle;
	_facing = Right;
	_animationCounter = 0;
	_imagePos.x = 0;
	_imagePos.y = IdleRight;
	_sprite.setTextureRect(IntRect(_imagePos.x, _imagePos.y, PLAYER_WIDTH, PLAYER_HEIGHT));
	_sprite.setPosition(State::getScreenWidth() / 2 - PLAYER_WIDTH * State::getScaleFactors().x / 2, 
		State::getScreenHeight() - GameState::getGroundHeight() - PLAYER_HEIGHT * State::getScaleFactors().y);
	_sprite.setColor(Color::White);
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
				if (_imagePos.x < IDLE_MAX_INDEX)
					_imagePos.x++;
				else
					_imagePos.x = 0;
			}
			break;
		case Moving:
			if (_animationCounter >= MOVING_FRAME_TIME)
			{
				_animationCounter = 0;
				if (_imagePos.x < MOVING_MAX_INDEX)
					_imagePos.x++;
				else
					_imagePos.x = 0;
			}
			break;
		case Jumping:
			if (_animationCounter >= JUMPING_FRAME_TIME)
			{
				_animationCounter = 0;
				if (_imagePos.x < JUMPING_MAX_INDEX)
					_imagePos.x++;
			}
			break;
	}
}