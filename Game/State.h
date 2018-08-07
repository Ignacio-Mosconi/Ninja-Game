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
	static Vector2f _scaleFactors;

	virtual void input() = 0;
	virtual void update(float elapsed) = 0;
	virtual void draw() const = 0;

public:
	State(RenderWindow& window);
	~State();

	int static getScreenWidth() { return _screenDimensions.x; }
	int static getScreenHeight() { return _screenDimensions.y; }
	Vector2f static getScaleFactors() { return _scaleFactors; }
	void static setScreenDimensions(Vector2u screenDimensions) { _screenDimensions = screenDimensions; }
	void static setScaleFactors(Vector2f scaleFactors) { _scaleFactors = scaleFactors; }
};

#endif
