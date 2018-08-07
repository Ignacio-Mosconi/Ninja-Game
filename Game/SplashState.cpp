#include "SplashState.h"

SplashState::SplashState(RenderWindow& window, const string& logoPath) : State(window),
_onScreenTime(0), _fadeTime(0), _start(false)
{
	_logoTexture.loadFromFile(logoPath);
	_logoTexture.setSmooth(true);
	_logo.setTexture(_logoTexture);
	_logo.setOrigin(_logo.getGlobalBounds().width / 2, _logo.getGlobalBounds().height / 2);
	_logo.scale(getScaleFactors());
	_logo.setPosition(getScreenWidth() / 2, getScreenHeight() / 2);
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
	if (_onScreenTime < SPLASH_STATE_DURATION / 3)
		_fadeTime += elapsed;
	else
		if (_onScreenTime > SPLASH_STATE_DURATION * 2/3)
			_fadeTime -= elapsed;
	
	float alphaMultiplier = std::max(0.0f, std::min(_fadeTime / (SPLASH_STATE_DURATION / 3), SPLASH_STATE_DURATION / 3));
	Color newColor(255, 255, 255, 255 * alphaMultiplier);
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