#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include "Definitions.h"
using namespace std;
using namespace sf;

class State
{
protected:
	RenderWindow* _window;
	Clock* _clock;

	static Vector2u _screenDimensions;

	virtual void input() = 0;
	virtual void update(float elapsed) = 0;
	virtual void draw() const = 0;

public:
	State(RenderWindow& window);
	~State();

	int static getScreenWidth() { return _screenDimensions.x; }
	int static getScreenHeight() { return _screenDimensions.y; }
	void static setScreenDimensions(Vector2u screenDimensions) { _screenDimensions = screenDimensions; }
};

#endif
