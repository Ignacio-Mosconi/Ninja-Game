#include "SplashState.h"

SplashState::SplashState(RenderWindow& window, const string& logoPath) : State(window)
{
	_logoTexture.loadFromFile(logoPath);
	_logo.setTexture(_logoTexture);
	_logo.setOrigin(_logo.getGlobalBounds().width / 2, _logo.getGlobalBounds().height / 2);
	_logo.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	_onScreenTime = 0;
	_start = false;
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
	if (_onScreenTime >= SPLASH_STATE_DURATION)
		_start = true;
}

void SplashState::draw()
{
	_window->clear(Color::Black);
	_window->draw(_logo);
	_window->display();
}