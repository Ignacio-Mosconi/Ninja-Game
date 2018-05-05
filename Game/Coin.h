#ifndef COIN_H
#define COIN_H

#include "Collectible.h"

class Coin : public Collectible
{
public:
	Coin(int x, int y, const string& imagePath);
	~Coin();

	void update(float elapsed);

	void respawn();
};

#endif