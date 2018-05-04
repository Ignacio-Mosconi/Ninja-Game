#ifndef LIFE_H
#define LIFE_H

#include "Collectible.h"
#include "Definitions.h"

class Life : public Collectible
{
protected:
	void flicker(float elapsed);

public:
	Life(int x, int y, const string& imagePath);
	~Life();

	void update(float elapsed);

	void respawn();
};

#endif