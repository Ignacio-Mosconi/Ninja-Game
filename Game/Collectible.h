#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "Entity.h"

class Collectible : public Entity
{
protected:
	bool _enabled;
	float _spawnTime;
	float _onScreenTime;
	float _flickeringCounter;
	int _imagePosX;
	float _animationCounter;
	static int _minY;

	virtual void flicker(float elapsed);
	virtual void animate(float elapsed) = 0;
	
public:
	Collectible(int x, int y, const string& imagePath, float spawnTime, float onScreenTime);

	virtual void update(float elapsed) = 0;

	void disable();
	virtual void respawn() = 0;

	inline bool isEnabled() { return _enabled; }
	void static setMinY(int minY) { _minY = minY; }
};

#endif;
