#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "State.h"
using namespace std;

class SplashState : public State
{
private:
	Texture _logoTexture;
	Sprite _logo;
	float _onScreenTime;
	bool _start;

protected:
	void input();
	void update(float elapsed);
	void draw(float elapsed);

public:
	SplashState(RenderWindow& window, const string &logoPath);
	~SplashState();

	void start();
};

#endif
