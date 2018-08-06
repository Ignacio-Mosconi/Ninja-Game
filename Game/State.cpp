#include "State.h"

Vector2u State::_screenDimensions = Vector2u(0, 0);
Vector2f State::_scaleFactor = Vector2f(0, 0);

State::State(RenderWindow& window)
{
	_window = &window;
	_clock = new Clock();
}

State::~State()
{
	delete _clock;
}