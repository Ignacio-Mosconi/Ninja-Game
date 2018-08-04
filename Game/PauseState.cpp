#include "PauseState.h"
#include "UtilityFunctions.h"

PauseState::PauseState(RenderWindow& window) : State(window),
_mouseX(0), _mouseY(0), _clicked(false), _resumeGame(false), _quitGame(false)
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

	_alphaRect.setSize(Vector2f(_window->getSize().x, _window->getSize().y));
	Color rectColor(0, 0, 0, ALPHA_RECT_VALUE);
	_alphaRect.setFillColor(rectColor);

	for (int i = 0; i < PAUSE_OPTIONS; i++)
		_selected[i] = false;
}

PauseState::~PauseState()
{
	delete _title;
	for (int i = 0; i < PAUSE_OPTIONS; i++)
		delete _options[i];
}

void PauseState::show(Sprite& background)
{
	_window->setMouseCursorVisible(true);
	_background = background;

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
	_window->setMouseCursorVisible(false);
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
			case Event::KeyPressed:
				if (event.key.code == Keyboard::ESCAPE_KEY)
					_resumeGame = true;
				break;
			case Event::JoystickButtonPressed:
				if (event.joystickButton.button == ESCAPE_BUTTON)
					_resumeGame = true;
				break;
		}
	}
}

void PauseState::update(float elapsed)
{
	for (int i = 0; i < PAUSE_OPTIONS; i++)
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
			_resumeGame = true;
		else
			if (_selected[1])
				_quitGame = true;
		_clicked = false;
	}
}

void PauseState::draw() const
{
	_window->clear();

	_window->draw(_background);

	_window->draw(_alphaRect);

	_window->draw(*_title);
	for (int i = 0; i < PAUSE_OPTIONS; i++)
		_window->draw(*_options[i]);

	_window->display();
}