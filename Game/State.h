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

	virtual void input() = 0;
	virtual void update(float elapsed) = 0;
	virtual void draw() const = 0;

public:
	State(RenderWindow& window);
	~State();
};

#endif
