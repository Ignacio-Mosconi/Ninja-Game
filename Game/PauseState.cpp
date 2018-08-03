#include "PauseState.h"
#include "UtilityFunctions.h"

PauseState::PauseState(RenderWindow& window) : State(window)
{
	_font.loadFromFile(FONT_PATH);

	_title = new Text("Paused", _font, PAUSED_TEXT_SIZE);
	_options[0] = new Text("Resume", _font, PAUSED_OPTIONS_TEXT_SIZE);
	_options[1] = new Text("Quit", _font, PAUSED_OPTIONS_TEXT_SIZE);

	formatText(_title, SCREEN_WIDTH / 2 - _title->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 4 - _title->getGlobalBounds().height / 2, TEXT_COLOR_GREEN, Color::White, true);
	formatText(_options[0], SCREEN_WIDTH / 2 - _options[0]->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _options[0]->getGlobalBounds().height / 2, Color::White);
	formatText(_options[1], SCREEN_WIDTH / 2 - _options[1]->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 + 128 - _options[1]->getGlobalBounds().height / 2, Color::White);

	_selectBuffer.loadFromFile(SELECT_SOUND);
	_select.setBuffer(_selectBuffer);

	_resumeBuffer.loadFromFile(RESUME_SOUND);
	_resume.setBuffer(_resumeBuffer);

	for (int i = 0; i < MENU_OPTIONS; i++)
		_selected[i] = false;
}

PauseState::~PauseState()
{
	delete _title;
	for (int i = 0; i < MENU_OPTIONS; i++)
		delete _options[i];
}

void PauseState::show()
{
	_window->setMouseCursorVisible(true);

	while (!_resumeGame && !_quitGame && _window->isOpen())
	{
		float elapsed = _clock->restart().asSeconds();

		input();
		update(elapsed);
		draw();
	}
	if (!_quitGame)
		resume();
}

void PauseState::resume()
{
	_resume.play();
	_resumeGame = false;
}

void PauseState::input()
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

void PauseState::update(float elapsed)
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
			_resumeGame = true;
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

void PauseState::draw() const
{
	_window->clear();

	_window->draw(*_title);
	for (int i = 0; i < MENU_OPTIONS; i++)
		_window->draw(*_options[i]);

	_window->display();
}