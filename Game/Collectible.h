#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "Entity.h"

class Collectible : public Entity
{
protected:
	bool _enabled;
	float _spawnTime;
	float _onScreenTime;
	
public:
	Collectible(int x, int y, const string& imagePath);

	virtual void update(float elapsed) = 0;

	void disable();
	virtual void respawn() = 0;

	inline bool isEnabled() { return _enabled; }
};

#endif;
