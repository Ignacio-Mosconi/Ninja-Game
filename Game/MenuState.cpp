#include "MenuState.h"
#include "UtilityFunctions.h"

MenuState::MenuState(RenderWindow& window) : State(window),
_mouseX(0), _mouseY(0), _clicked(false), _startGame(false), _currentScreen(Main)
{
	_font.loadFromFile(FONT_PATH);

	_title = new Text("Ninja Thief", _font, TITLE_TEXT_SIZE * getScaleFactors().x);
	_options[0] = new Text("Play", _font, OPTIONS_TEXT_SIZE * getScaleFactors().x);
	_options[1] = new Text("Leaderboard", _font, OPTIONS_TEXT_SIZE * getScaleFactors().x);
	_options[2] = new Text("Credits", _font, OPTIONS_TEXT_SIZE * getScaleFactors().x);
	_options[3] = new Text("Exit", _font, OPTIONS_TEXT_SIZE * getScaleFactors().x);

	_creditsTitle = new Text("Credits", _font, SUB_TITLE_TEXT_SIZE * getScaleFactors().x);
	_credits[0] = new Text("Game Director", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_credits[1] = new Text("Game Designer", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_credits[2] = new Text("Lead Programmer", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_credits[3] = new Text("Lead Artist", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_credits[4] = new Text("Sound Effects By", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_credits[5] = new Text("Music By", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	for (int i = 0; i < CREDITS_ITEMS - 1; i++)
		_names[i] = new Text("Ignacio Mosconi", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_names[4] = new Text("Bfxr", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_names[5] = new Text("Ignacio Mosconi", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_poweredBySFML = new Text("Powered By SFML 2.5.0", _font, CREDITS_TEXT_SIZE * getScaleFactors().x);
	_creditsOptions[0] = new Text("Back", _font, OPTIONS_TEXT_SIZE * getScaleFactors().x);

	_leaderboardTitle = new Text("Leaderboard", _font, SUB_TITLE_TEXT_SIZE * getScaleFactors().x);
	_leaderboard = new Text("Highest Score: 0 ", _font, HIGHEST_SCORE_TEXT_SIZE * getScaleFactors().x);
	_leaderboardOptions[0] = new Text("Back", _font, OPTIONS_TEXT_SIZE * getScaleFactors().x);

	formatText(_title, getScreenWidth() / 2 - _title->getGlobalBounds().width / 2,
		getScreenHeight() / 3 - _title->getGlobalBounds().height / 2, Color::Red, Color::White, true);
	for (int i = 0; i < MENU_OPTIONS; i++)
		formatText(_options[i], getScreenWidth() / 2 - _options[i]->getGlobalBounds().width / 2,
			getScreenHeight() / 2 + 96 * (i + 1) * State::getScaleFactors().x - _options[i]->getGlobalBounds().height / 2, Color::White);

	formatText(_creditsTitle, getScreenWidth() / 2 - _creditsTitle->getGlobalBounds().width / 2,
		getScreenHeight() / 6 - _creditsTitle->getGlobalBounds().height / 2, Color::Red, Color::White, true);
	for (int i = 0; i < CREDITS_ITEMS; i++)
	{
		formatText(_credits[i], 32, getScreenHeight() * 2 / 5 + 64 * i * State::getScaleFactors().x -
			_credits[i]->getGlobalBounds().height / 2, TEXT_COLOR_GREEN);
		formatText(_names[i], getScreenWidth() - _names[i]->getGlobalBounds().width - 32,
			getScreenHeight() * 2 / 5 + 64 * i * getScaleFactors().x - _names[i]->getGlobalBounds().height / 2, Color::White);
	}
	formatText(_poweredBySFML, getScreenWidth() / 2 - _poweredBySFML->getGlobalBounds().width / 2,
		getScreenHeight() * 2/5 + 64 * 6 * getScaleFactors().x - _poweredBySFML->getGlobalBounds().height / 2, 
		Color::Red, Color::White, true);
	formatText(_creditsOptions[0], getScreenWidth() - _creditsOptions[0]->getGlobalBounds().width - 32,
		getScreenHeight() - _creditsOptions[0]->getGlobalBounds().height - 32, Color::White);

	formatText(_leaderboardTitle, getScreenWidth() / 2 - _leaderboardTitle->getGlobalBounds().width / 2,
		getScreenHeight() / 6 - _leaderboardTitle->getGlobalBounds().height / 2, Color::Red, Color::White, true);
	formatText(_leaderboard, getScreenWidth() / 2 - _leaderboard->getGlobalBounds().width / 2,
		getScreenHeight() / 2 - _leaderboard->getGlobalBounds().height / 2, Color::White);
	formatText(_leaderboardOptions[0], getScreenWidth() - _leaderboardOptions[0]->getGlobalBounds().width - 32,
		getScreenHeight() - _leaderboardOptions[0]->getGlobalBounds().height - 32, Color::White);

	_selectBuffer.loadFromFile(SELECT_SOUND);
	_select.setBuffer(_selectBuffer);

	for (int i = 0; i < MENU_OPTIONS; i++)
		_selected[i] = false;
	for (int i = 0; i < CREDITS_OPTIONS; i++)
		_creditsSelected[i] = false;
	for (int i = 0; i < HIGHEST_SCORE_OPTIONS; i++)
		_highestScoreSelected[i] = false;
}

MenuState::~MenuState()
{
	delete _title;
	delete _creditsTitle;
	delete _leaderboardTitle;
	for (int i = 0; i < MENU_OPTIONS; i++)
		delete _options[i];
	for (int i = 0; i < CREDITS_OPTIONS; i++)
		delete _creditsOptions[i];
	for (int i = 0; i < HIGHEST_SCORE_OPTIONS; i++)
		delete _leaderboardOptions[i];
	for (int i = 0; i < CREDITS_ITEMS; i++)
	{
		delete _credits[i];
		delete _names[i];
	}
	delete _poweredBySFML;
	delete _leaderboard;
}

void MenuState::show()
{
	_window->setMouseCursorVisible(true);

	while (!_startGame && _window->isOpen())
	{
		float elapsed = _clock->restart().asSeconds();

		input();
		update(elapsed);
		draw();
	}
}

void MenuState::input()
{
	Event event;

	if (_window->pollEvent(event))
	{
		switch (event.type)
		{
			case Event::Closed:
				_window->close();
				break;
			case Event::MouseMoved:
				_mouseX = event.mouseMove.x;
				_mouseY = event.mouseMove.y;
				break;
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					_mouseX = event.mouseButton.x;
					_mouseY = event.mouseButton.y;
					_clicked = true;
				}
				break;
		}
	}
}

void MenuState::update(float elapsed)
{
	switch (_currentScreen)
	{
		case Main:
			for (int i = 0; i < MENU_OPTIONS; i++)
			{
				if (_options[i]->getGlobalBounds().contains(_mouseX, _mouseY))
				{
					if (!_selected[i])
					{
						_select.play();
						_selected[i] = true;
						_options[i]->setFillColor(TEXT_COLOR_RED);
					}
				}
				else
				{
					if (_selected[i])
					{
						_selected[i] = false;
						_options[i]->setFillColor(Color::White);
					}
				}
			}

			if (_clicked)
			{
				if (_selected[0])
				{
					_window->setMouseCursorVisible(false);
					_startGame = true;
				}
				else
				{
					if (_selected[1])
						_currentScreen = Leaderboard;
					else
					{
						if (_selected[2])
							_currentScreen = Credits;
						else
							if (_selected[3])
								_window->close();
					}
				}
				_clicked = false;
			}
			break;

		case Leaderboard:
			for (int i = 0; i < HIGHEST_SCORE_OPTIONS; i++)
			{
				if (_leaderboardOptions[i]->getGlobalBounds().contains(_mouseX, _mouseY))
				{
					if (!_highestScoreSelected[i])
					{
						_select.play();
						_highestScoreSelected[i] = true;
						_leaderboardOptions[i]->setFillColor(TEXT_COLOR_RED);
					}
				}
				else
				{
					if (_highestScoreSelected[i])
					{
						_highestScoreSelected[i] = false;
						_leaderboardOptions[i]->setFillColor(Color::White);
					}
				}
			}

			if (_clicked)
			{
				if (_highestScoreSelected[0])
					_currentScreen = Main;
				_clicked = false;
			}
			break;

		case Credits:
			for (int i = 0; i < CREDITS_OPTIONS; i++)
			{
				if (_creditsOptions[i]->getGlobalBounds().contains(_mouseX, _mouseY))
				{
					if (!_creditsSelected[i])
					{
						_select.play();
						_creditsSelected[i] = true;
						_creditsOptions[i]->setFillColor(TEXT_COLOR_RED);
					}
				}
				else
				{
					if (_creditsSelected[i])
					{
						_creditsSelected[i] = false;
						_creditsOptions[i]->setFillColor(Color::White);
					}
				}
			}

			if (_clicked)
			{
				if (_creditsSelected[0])
					_currentScreen = Main;
				_clicked = false;
			}
			break;
	}
}


void MenuState::draw() const
{
	_window->clear();

	switch (_currentScreen)
	{
		case Main:
			_window->draw(*_title);
			for (int i = 0; i < MENU_OPTIONS; i++)
				_window->draw(*_options[i]);
			break;
		case Leaderboard:
			_window->draw(*_leaderboardTitle);
			_window->draw(*_leaderboard);
			for (int i = 0; i < HIGHEST_SCORE_OPTIONS; i++)
				_window->draw(*_leaderboardOptions[i]);
			break;
		case Credits:
			_window->draw(*_creditsTitle);
			for (int i = 0; i < CREDITS_OPTIONS; i++)
				_window->draw(*_creditsOptions[i]);
			for (int i = 0; i < CREDITS_ITEMS; i++)
			{
				_window->draw(*_credits[i]);
				_window->draw(*_names[i]);
			}
			_window->draw(*_poweredBySFML);
			break;
	}

	_window->display();
}

void MenuState::changeHighestScore(const int& highestScore)
{
	_leaderboard->setString("Highest Score: " + to_string(highestScore));
	formatText(_leaderboard, getScreenWidth() / 2 - _leaderboard->getGlobalBounds().width / 2,
		getScreenHeight() / 2 - _leaderboard->getGlobalBounds().height / 2, Color::White);
}