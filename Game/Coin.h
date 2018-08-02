#ifndef COIN_H
#define COIN_H

#include "Collectible.h"

class Coin : public Collectible
{
protected:
	void animate(float elapsed);

public:
	Coin(int x, int y, const string& imagePath);
	virtual ~Coin();

	void update(float elapsed);

	void respawn();
};

#endif