#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

enum PlayerState
{
	Idle,
	Moving,
	Jumping,
	Falling
};

enum Facing
{
	Left,
	Right
};

enum Collectables
{
	Coins,
	LifeBonuses
};

enum Animation
{
	IdleRight,
	IdleLeft,
	MovingRight,
	MovingLeft,
	JumpingRight,
	JumpingLeft
};

class Player : public Entity
{
private:
	SoundBuffer _jumpBuffer;
	SoundBuffer _fruitHitBuffer;
	SoundBuffer _pickUpCoinBuffer;
	SoundBuffer _pickUpLifeBuffer;

	Sound _jump;
	Sound _fruitHit;
	Sound _pickUpCoin;
	Sound _pickUpLife;

	PlayerState _currentState;
	Facing _facing;
	Vector2i _imagePos;
	float _animationCounter;

	int _lives;
	float _moveSpeed;
	float _jumpSpeed;
	bool _isInvincible;
	float _flickeringTime;
	float _flickeringCounter;

	void move(float elapsed);
	void jump(float elapsed);
	void fall(float elapsed);
	void flicker(float elapsed);
	void animate(float elapsed);

public:
	Player(int x, int y, const string& imagePath);
	~Player();

	void update(float elapsed);
	bool pickUpItem(Collectables collectable);
	void die();
	void respawn();

	inline PlayerState getCurrentState() { return _currentState; }
	inline int getLives() { return _lives; }
	inline bool isFlickering() { return _isInvincible; }
	void setLives(int lives) { _lives = lives; }
};

#endif