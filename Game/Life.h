#ifndef LIFE_H
#define LIFE_H

#include "Collectible.h"

class Life : public Collectible
{
protected:
	void animate(float elapsed);

public:
	Life(int x, int y, const string& imagePath);
	~Life();

	void update(float elapsed);

	void respawn();
};

#endif