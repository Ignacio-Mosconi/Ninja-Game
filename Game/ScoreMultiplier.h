#ifndef SCORE_MULTIPLIER_H
#define SCORE_MULTIPLIER_H

#include "Collectible.h"

class ScoreMultiplier : public Collectible
{
protected:
	void animate(float elapsed);

public:
	ScoreMultiplier(int x, int y, const string& imagePath);
	virtual ~ScoreMultiplier();

	void update(float elapsed);

	void respawn();
};

#endif
