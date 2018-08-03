#include "EndGameState.h"
#include "UtilityFunctions.h"

EndGameState::EndGameState(RenderWindow& window) : State(window)
{
	_font.loadFromFile(FONT_PATH);

	_title = new Text("Game Over", _font, END_GAME_TEXT_SIZE);
	_options[0] = new Text("Restart", _font, END_GAME_OPTIONS_TEXT_SIZE);
	_options[1] = new Text("Quit", _font, END_GAME_OPTIONS_TEXT_SIZE);

	formatText(_title, SCREEN_WIDTH / 2 - _title->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 4 - _title->getGlobalBounds().height / 2, TEXT_COLOR_RED, Color::Red, true);
	formatText(_options[0], 32, SCREEN_HEIGHT - _options[0]->getGlobalBounds().height - 90,
		Color::White, TEXT_COLOR_BLUE, true);
	formatText(_options[1], SCREEN_WIDTH - _options[1]->getGlobalBounds().width - 32,
		SCREEN_HEIGHT - _options[1]->getGlobalBounds().height - 90, Color::White, Color::Red, true);

	_selectBuffer.loadFromFile(SELECT_SOUND);
	_select.setBuffer(_selectBuffer);

	_alphaRect.setSize(Vector2f(_window->getSize().x, _window->getSize().y));
	Color rectColor(0, 0, 0, ALPHA_RECT_VALUE);
	_alphaRect.setFillColor(rectColor);

	for (int i = 0; i < MENU_OPTIONS; i++)
		_selected[i] = false;
}

EndGameState::~EndGameState()
{
	delete _title;
	for (int i = 0; i < MENU_OPTIONS; i++)
		delete _options[i];
}

void EndGameState::show(Sprite& background)
{
	_window->setMouseCursorVisible(true);
	_background = background;

	while (!_restartGame && !_quitGame && _window->isOpen())
	{
		float elapsed = _clock->restart().asSeconds();

		input();
		update(elapsed);
		draw();
	}
	if (!_quitGame)
		restart();
}

void EndGameState::restart()
{
	_window->setMouseCursorVisible(false);
	_restartGame = false;
}

void EndGameState::input()
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

void EndGameState::update(float elapsed)
{
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
			_restartGame = true;
			_clicked = false;
		}
		else
			if (_selected[1])
			{
				_quitGame = true;
				_clicked = false;
			}
	}

}

void EndGameState::draw() const
{
	_window->clear();

	_window->draw(_background);

	_window->draw(_alphaRect);

	_window->draw(*_title);
	for (int i = 0; i < MENU_OPTIONS; i++)
		_window->draw(*_options[i]);

	_window->display();
}