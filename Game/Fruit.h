#ifndef FRUIT_H
#define FRUIT_H

#include "Entity.h"
#include "Definitions.h"

class Fruit : public Entity
{
private:
	float _speed;
	float _rotationSpeed;
	float _spawnTime;
	bool _enabled;

	void move(float elapsed);

public:
	Fruit(int x, int y, const string& imagePath);
	~Fruit();

	void update(float elapsed);

	void disable();
	void respawn();

	inline bool isEnabled() { return _enabled; }
};

#endif
