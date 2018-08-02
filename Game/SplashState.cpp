#include "SplashState.h"

SplashState::SplashState(RenderWindow& window, const string& logoPath) : State(window),
_onScreenTime(0), _start(false)
{
	_logoTexture.loadFromFile(logoPath);
	_logo.setTexture(_logoTexture);
	_logo.setOrigin(_logo.getGlobalBounds().width / 2, _logo.getGlobalBounds().height / 2);
	_logo.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

SplashState::~SplashState()
{
}

void SplashState::start()
{
	while (_window->isOpen() && !_start)
	{
		float elapsed = _clock->restart().asSeconds();

		input();
		update(elapsed);
		draw();
	}
}

void SplashState::input()
{
	Event event;

	if (_window->pollEvent(event))
		switch (event.type)
		{
		case Event::Closed:
			_window->close();
			break;
		}
}

void SplashState::update(float elapsed)
{
	_onScreenTime += elapsed;
	
	Color newColor(255, 255, 255, 255 * (_onScreenTime / SPLASH_STATE_DURATION));
	_logo.setColor(newColor);
	if (_onScreenTime >= SPLASH_STATE_DURATION)
		_start = true;
}

void SplashState::draw() const
{
	_window->clear();
	_window->draw(_logo);
	_window->display();
}