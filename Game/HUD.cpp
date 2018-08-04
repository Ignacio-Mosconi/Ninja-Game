#include "HUD.h"
#include "UtilityFunctions.h"

HUD::HUD() : _showScoreMultBonus(false)
{
	_font.loadFromFile(FONT_PATH);

	_lives = new Text("Lives: 3", _font, HUD_TEXT_SIZE);
	_score = new Text("Score: 0", _font, HUD_TEXT_SIZE);
	_time = new Text("Time: 120", _font, HUD_TEXT_SIZE);
	_scoreMult = new Text("Score x2", _font, HUD_SCORE_MULT_TEXT_SIZE);

	formatText(_lives, 32, HUD_TEXT_Y, TEXT_COLOR_GREEN, Color::White, true);
	formatText(_score, SCREEN_WIDTH / 2 - _score->getGlobalBounds().width / 2, HUD_TEXT_Y, TEXT_COLOR_BLUE, Color::White, true);
	formatText(_time, SCREEN_WIDTH - _time->getGlobalBounds().width - 32, HUD_TEXT_Y, TEXT_COLOR_GREEN, Color::White, true);
	formatText(_scoreMult, 32, SCREEN_HEIGHT - _scoreMult->getGlobalBounds().height - 32, TEXT_COLOR_YELLOW, Color::Green, true);

	_clockTickBuffer.loadFromFile(CLOCK_TICK_SOUND);
	_clockTick.setBuffer(_clockTickBuffer);
}

HUD::~HUD()
{
	delete _lives;
	delete _score;
	delete _time;
	delete _scoreMult;
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
			formatText(_score, SCREEN_WIDTH / 2 - _score->getGlobalBounds().width / 2, HUD_TEXT_Y, TEXT_COLOR_BLUE, Color::White, true);
			break;
		case TimeLeft:
			_time->setString("Time: " + to_string(number));
			if (number > 60)
				_time->setFillColor(TEXT_COLOR_GREEN);
			else
			{
				if (number > 20)
					_time->setFillColor(TEXT_COLOR_YELLOW);
				else
				{
					_time->setFillColor(TEXT_COLOR_RED);
					if (number <= 10)
						_clockTick.play();
				}
			}
			break;
		case ScoreMultBonus:
			_showScoreMultBonus = !_showScoreMultBonus;
			break;
	}
}

void HUD::draw(RenderWindow* window)
{
	window->draw(*_lives);
	window->draw(*_score);
	window->draw(*_time);
	if (_showScoreMultBonus)
		window->draw(*_scoreMult);
}
