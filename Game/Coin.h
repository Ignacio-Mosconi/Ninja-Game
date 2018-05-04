#ifndef COIN_H
#define COIN_H

#include "Collectible.h"
#include "Definitions.h"

class Coin : public Collectible
{
protected:
	void flicker(float elapsed);

public:
	Coin(int x, int y, const string& imagePath);
	~Coin();

	void update(float elapsed);

	void respawn();
};

#endif