#include "HUD.h"

HUD::HUD()
{
	_font.loadFromFile(FONT_PATH);

	_lives = new Text("Lives: 3", _font, HUD_TEXT_SIZE);
	_score = new Text("Score: 0", _font, HUD_TEXT_SIZE);
	_paused = new Text("Paused", _font, PAUSED_TEXT_SIZE);
	_gameOver = new Text("Game Over", _font, GAME_OVER_TEXT_SIZE);
	_restart = new Text("Press enter to restart", _font, HUD_OPTIONS_TEXT_SIZE);
	_quit = new Text("Press escape to quit", _font, HUD_OPTIONS_TEXT_SIZE);
	_youScored = new Text("You scored: 0", _font, HUD_OPTIONS_TEXT_SIZE);
	_highestScore = new Text("Highest Score: 0", _font, HUD_OPTIONS_TEXT_SIZE);
	_credits = new Text("Made by Ignacio Mosconi - Powered by SFML 2.4", _font, HUD_OPTIONS_TEXT_SIZE);

	formatText(_lives, 32, HUD_TEXT_Y, TEXT_COLOR_GREEN, Color::White, true);
	formatText(_score, SCREEN_WIDTH / 2 - _score->getGlobalBounds().width / 2, HUD_TEXT_Y, TEXT_COLOR_BLUE, Color::White, true);
	formatText(_paused, SCREEN_WIDTH / 2 - _paused->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _paused->getGlobalBounds().height /2, TEXT_COLOR_GREEN, Color::White, true);
	formatText(_gameOver, SCREEN_WIDTH / 2 - _gameOver->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 4 - _gameOver->getGlobalBounds().height / 2, TEXT_COLOR_RED, Color::Red, true);
	formatText(_restart, 32, SCREEN_HEIGHT - _restart->getGlobalBounds().height - 90, TEXT_COLOR_GREEN, TEXT_COLOR_BLUE, true);
	formatText(_quit, SCREEN_WIDTH - _quit->getGlobalBounds().width - 32, SCREEN_HEIGHT - _restart->getGlobalBounds().height - 90,
		TEXT_COLOR_RED, Color::Red, true);
	formatText(_youScored, SCREEN_WIDTH / 2 - _youScored->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _youScored->getGlobalBounds().height / 2, Color::White, Color::Black, true);
	formatText(_highestScore, SCREEN_WIDTH / 2 - _highestScore->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _highestScore->getGlobalBounds().height / 2 + 64, Color::White, Color::Black, true);
	formatText(_credits, SCREEN_WIDTH / 2 - _credits->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _credits->getGlobalBounds().height / 2 + 192, Color::Black, TEXT_COLOR_GREEN, true);
}

HUD::~HUD()
{
	delete _lives;
	delete _score;
	delete _paused;
	delete _gameOver;
	delete _youScored;
	delete _highestScore;
	delete _credits;
}

void HUD::updateHUD(Element element, int number)
{
	switch (element)
	{
		case Lives:
			_lives->setString("Lives: " + to_string(number));
			switch (number)
			{
				case 1:
					_lives->setFillColor(TEXT_COLOR_RED);
					break;
				case 2:
					_lives->setFillColor(TEXT_COLOR_YELLOW);
					break;
				case 3:
					_lives->setFillColor(TEXT_COLOR_GREEN);
					break;
			}
			break;
		case Score:
			_score->setString("Score: " + to_string(number));
			break;
		case HighestScore:
			_highestScore->setString("Highest Score: " + to_string(number));
			break;
		case FinalScore:
			_youScored->setString("You Scored: " + to_string(number));
			break;
	}
}

void HUD::draw(RenderWindow* window, bool isPaused, bool isGameOver)
{
	if (!isGameOver)
	{
		window->draw(*_lives);
		window->draw(*_score);
		if (isPaused)
			window->draw(*_paused);
	}
	else
	{
		window->draw(*_gameOver);
		window->draw(*_restart);
		window->draw(*_quit);
		window->draw(*_youScored);
		window->draw(*_highestScore);
		window->draw(*_credits);
	}
}

void HUD::formatText(Text* text, int x, int y, Color fillColor, Color outlineColor, bool outline)
{
	text->setFillColor(fillColor);
	if (outline)
	{
		text->setOutlineThickness(3);
		text->setOutlineColor(outlineColor);
	}
	text->setPosition(x, y);
}
