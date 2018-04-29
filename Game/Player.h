#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Definitions.h"

class Player : public Entity
{
private:
	float _speed;

	void move(float elapsed);
	void jump();

public:
	Player(int x, int y, const string& imagePath);
	~Player();

	void update(float elapsed);
};

#endif