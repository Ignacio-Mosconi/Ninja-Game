#include "MenuState.h"
#include "UtilityFunctions.h"

MenuState::MenuState(RenderWindow& window) : State(window),
_mouseX(0), _mouseY(0), _clicked(false), _startGame(false), _currentScreen(Main)
{
	_font.loadFromFile(FONT_PATH);

	_title = new Text("Ninja Thief", _font, TITLE_TEXT_SIZE);
	_options[0] = new Text("Play", _font, OPTIONS_TEXT_SIZE);
	_options[1] = new Text("Credits", _font, OPTIONS_TEXT_SIZE);
	_options[2] = new Text("Exit", _font, OPTIONS_TEXT_SIZE);

	_creditsTitle = new Text("Credits", _font, SUB_TITLE_TEXT_SIZE);
	_credits[0] = new Text("Game Director", _font, CREDITS_TEXT_SIZE);
	_credits[1] = new Text("Game Designer", _font, CREDITS_TEXT_SIZE);
	_credits[2] = new Text("Gameplay Programmer", _font, CREDITS_TEXT_SIZE);
	_credits[3] = new Text("Lead Artist", _font, CREDITS_TEXT_SIZE);
	_credits[4] = new Text("Sound Effects By", _font, CREDITS_TEXT_SIZE);
	_credits[5] = new Text("Music By", _font, CREDITS_TEXT_SIZE);
	for (int i = 0; i < CREDITS_ITEMS - 1; i++)
		_names[i] = new Text("Ignacio Mosconi", _font, CREDITS_TEXT_SIZE);
	_names[4] = new Text("Bfxr", _font, CREDITS_TEXT_SIZE);
	_names[5] = new Text("Ignacio Mosconi", _font, CREDITS_TEXT_SIZE);
	_poweredBySFML = new Text("Powered By SFML 2.5.0", _font, CREDITS_TEXT_SIZE);

	_creditsOptions[0] = new Text("Back", _font, OPTIONS_TEXT_SIZE);

	formatText(_title, SCREEN_WIDTH / 2 - _title->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 3 - _title->getGlobalBounds().height / 2, Color::Red, Color::White, true);
	for (int i = 0; i < MENU_OPTIONS; i++)
		formatText(_options[i], SCREEN_WIDTH / 2 - _options[i]->getGlobalBounds().width / 2,
			SCREEN_HEIGHT / 2 + 96 * (i + 1) - _options[i]->getGlobalBounds().height / 2, Color::White);

	formatText(_creditsTitle, SCREEN_WIDTH / 2 - _creditsTitle->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 6 - _creditsTitle->getGlobalBounds().height / 2, Color::Red, Color::White, true);
	for (int i = 0; i < CREDITS_ITEMS; i++)
	{
		formatText(_credits[i], 32, SCREEN_HEIGHT * 2 / 5 + 64 * i - _credits[i]->getGlobalBounds().height / 2, TEXT_COLOR_GREEN);
		formatText(_names[i], SCREEN_WIDTH - _names[i]->getGlobalBounds().width - 32,
			SCREEN_HEIGHT * 2 / 5 + 64 * i - _names[i]->getGlobalBounds().height / 2, Color::White);
	}
	formatText(_poweredBySFML, SCREEN_WIDTH / 2 - _poweredBySFML->getGlobalBounds().width / 2,
		SCREEN_HEIGHT * 2/5 + 64 * 6 - _poweredBySFML->getGlobalBounds().height / 2, Color::Red);

	formatText(_creditsOptions[0], SCREEN_WIDTH - _creditsOptions[0]->getGlobalBounds().width - 32,
		SCREEN_HEIGHT - _creditsOptions[0]->getGlobalBounds().height - 32, Color::White);

	_selectBuffer.loadFromFile(SELECT_SOUND);
	_select.setBuffer(_selectBuffer);

	for (int i = 0; i < MENU_OPTIONS; i++)
		_selected[i] = false;
	for (int i = 0; i < CREDITS_OPTIONS; i++)
		_creditsSelected[i] = false;
}

MenuState::~MenuState()
{
	delete _title;
	for (int i = 0; i < MENU_OPTIONS; i++)
		delete _options[i];
	for (int i = 0; i < CREDITS_OPTIONS; i++)
		delete _creditsOptions[i];
	for (int i = 0; i < CREDITS_ITEMS; i++)
	{
		delete _credits[i];
		delete _names[i];
	}
	delete _poweredBySFML;
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
						_currentScreen = Credits;
					else
						if (_selected[2])
							_window->close();
				}
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