#ifndef LIFE_H
#define LIFE_H

#include "Collectible.h"

class Life : public Collectible
{
public:
	Life(int x, int y, const string& imagePath);
	~Life();

	void update(float elapsed);

	void respawn();
};

#endif