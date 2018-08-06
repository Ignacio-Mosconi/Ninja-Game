#ifndef FRUIT_H
#define FRUIT_H

#include "Entity.h"

enum Kind
{
	Watermelon,
	Apple,
	Pear,
	Banana
};

class Fruit : public Entity
{
private:
	SoundBuffer _crashBuffer;
	Sound _crash;

	Kind _kind;
	float _speed;
	float _rotationSpeed;
	float _spawnTime;
	bool _enabled;
	bool _hasReachedBottom;

	static float _gameTime;
	
	void move(float elapsed);
	Kind chooseKind();

public:
	Fruit(int x, int y, const string& imagePath);
	virtual ~Fruit();

	void update(float elapsed);

	void disable();
	void respawn();

	inline bool isEnabled() { return _enabled; }
	inline bool hasReachedBottom() { return _hasReachedBottom; }
	inline Kind getKind() { return _kind; }
	void setHasReachedBottom(bool value) { _hasReachedBottom = value; }
	float static getGameTime() { return _gameTime; }
	void static increaseGameTime(float elapsed) { _gameTime += elapsed; }
	void static resetGameTime() { _gameTime = 0; }
};

#endif
