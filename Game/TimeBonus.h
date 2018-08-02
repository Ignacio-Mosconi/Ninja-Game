#ifndef TIME_BONUS_H
#define TIME_BONUS_H

#include "Collectible.h"

class TimeBonus : public Collectible
{
protected:
	void animate(float elapsed);

public:
	TimeBonus(int x, int y, const string& imagePath);
	virtual ~TimeBonus();

	void update(float elapsed);

	void respawn();
};

#endif