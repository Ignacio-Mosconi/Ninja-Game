#include "State.h"

State::State(RenderWindow& window)
{
	_window = &window;
	_clock = new Clock();
}

State::~State()
{
	delete _clock;
}