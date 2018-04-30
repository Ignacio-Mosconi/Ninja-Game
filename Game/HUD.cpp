#include "HUD.h"

HUD::HUD()
{
	_font.loadFromFile(FONT_PATH);

	_lives = new Text("Lives: 3", _font, HUD_TEXT_SIZE);
	_score = new Text("Score: 0", _font, HUD_TEXT_SIZE);
	_paused = new Text("Paused", _font, PAUSED_TEXT_SIZE);
	_gameOver = new Text("Game Over", _font, GAME_OVER_TEXT_SIZE);

	formatText(_lives, 32, HUD_TEXT_Y, TEXT_COLOR_GREEN, Color::White, true);
	formatText(_score, SCREEN_WIDTH / 2 - _score->getGlobalBounds().width / 2, HUD_TEXT_Y, TEXT_COLOR_BLUE, Color::White, true);
	formatText(_paused, SCREEN_WIDTH / 2 - _paused->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _paused->getGlobalBounds().height /2, TEXT_COLOR_GREEN, Color::White, true);
	formatText(_gameOver, SCREEN_WIDTH / 2 - _gameOver->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _gameOver->getGlobalBounds().height / 2, TEXT_COLOR_RED, Color::Red, true);
}

HUD::~HUD()
{
	delete _lives;
	delete _score;
	delete _paused;
	delete _gameOver;
}

void HUD::updateHUD(Element element, int number)
{

}

void HUD::draw(RenderWindow* window, bool isPaused, bool isGameOver)
{
	window->draw(*_lives);
	window->draw(*_score);
	if  (isPaused)
		window->draw(*_paused);
	if (isGameOver)
		window->draw(*_gameOver);
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
