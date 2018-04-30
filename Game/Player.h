#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Definitions.h"

enum PlayerState
{
	Idle,
	Moving,
	Jumping,
	Falling
};

class Player : public Entity
{
private:
	PlayerState _currentState;
	float _moveSpeed;
	float _jumpSpeed;

	void move(float elapsed);
	void jump(float elapsed);
	void fall(float elapsed);

public:
	Player(int x, int y, const string& imagePath);
	~Player();

	void update(float elapsed);

	PlayerState getCurrentState() { return _currentState; }
};

#endif