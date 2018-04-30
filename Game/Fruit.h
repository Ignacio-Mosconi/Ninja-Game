#ifndef FRUIT_H
#define FRUIT_H

#include "Entity.h"
#include "Definitions.h"

class Fruit : public Entity
{
private:
	float _speed;

public:
	Fruit(int x, int y, const string& imagePath);
	~Fruit();

	void update(float elapsed);

	void respawn();
};

#endif
