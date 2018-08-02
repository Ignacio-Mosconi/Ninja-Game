#include "MenuState.h"

MenuState::MenuState(RenderWindow& window) : State(window)
{
	_font.loadFromFile(FONT_PATH);

	_title = new Text("Ninja Thief", _font, TITLE_TEXT_SIZE);
	_options[0] = new Text("Play", _font, OPTIONS_TEXT_SIZE);
	_options[1] = new Text("Exit", _font, OPTIONS_TEXT_SIZE);

	formatText(_title, SCREEN_WIDTH / 2 - _title->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 3 - _title->getGlobalBounds().height / 2, Color::Red, Color::White, true);
	formatText(_options[0], SCREEN_WIDTH / 2 - _options[0]->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 + 128- _options[0]->getGlobalBounds().height / 2, Color::White);
	formatText(_options[1], SCREEN_WIDTH / 2 - _options[1]->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 + 256 - _options[1]->getGlobalBounds().height / 2, Color::White);

	_selectBuffer.loadFromFile(SELECT_SOUND);
	_select.setBuffer(_selectBuffer);

	for (int i = 0; i < MENU_OPTIONS; i++)
		_selected[i] = false;
}

MenuState::~MenuState()
{
	delete _title;
	for (int i = 0; i < MENU_OPTIONS; i++)
		delete _options[i];
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
	for (int i = 0; i < MENU_OPTIONS; i++)
	{
		if (_options[i]->getGlobalBounds().contains(_mouseX, _mouseY))
		{
			if (!_selected[i])
			{
				_select.play();
				_selected[i] = true;
				_options[i]->setFillColor(TEXT_COLOR_GREEN);
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
			_clicked = false;
		}
		else
			if (_selected[1])
				_window->close();
	}

}

void MenuState::draw() const
{
	_window->clear(Color::Black);

	_window->draw(*_title);
	for (int i = 0; i < MENU_OPTIONS; i++)
		_window->draw(*_options[i]);

	_window->display();
}

void MenuState::formatText(Text* text, int x, int y, Color fillColor, Color outlineColor, bool outline)
{
	text->setFillColor(fillColor);
	if (outline)
	{
		text->setOutlineThickness(3);
		text->setOutlineColor(outlineColor);
	}
	text->setPosition(x, y);
}