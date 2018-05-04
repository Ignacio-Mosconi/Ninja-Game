#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Audio.hpp>
#include "Entity.h"
#include "Definitions.h"

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

	int _lives;
	float _moveSpeed;
	float _jumpSpeed;
	bool _isFlickering;
	float _flickeringTime;
	float _flickeringCounter;

	void move(float elapsed);
	void jump(float elapsed);
	void fall(float elapsed);
	void flicker(float elapsed);

public:
	Player(int x, int y, const string& imagePath);
	~Player();

	void update(float elapsed);
	bool pickUpItem(Collectables collectable);
	void die();
	void respawn();

	inline PlayerState getCurrentState() { return _currentState; }
	inline int getLives() { return _lives; }
	inline bool isFlickering() { return _isFlickering; }
	void setLives(int lives) { _lives = lives; }
};

#endif