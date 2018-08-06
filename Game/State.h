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
	static Vector2f _scaleFactor;

	virtual void input() = 0;
	virtual void update(float elapsed) = 0;
	virtual void draw() const = 0;

public:
	State(RenderWindow& window);
	~State();

	int static getScreenWidth() { return _screenDimensions.x; }
	int static getScreenHeight() { return _screenDimensions.y; }
	Vector2f static getScaleFactor() { return _scaleFactor; }
	void static setScreenDimensions(Vector2u screenDimensions) { _screenDimensions = screenDimensions; }
	void static setScaleFactor(Vector2f scaleFactor) { _scaleFactor = scaleFactor; }
};

#endif
