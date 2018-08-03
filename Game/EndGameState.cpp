#include "EndGameState.h"
#include "UtilityFunctions.h"

EndGameState::EndGameState(RenderWindow& window) : State(window),
_mouseX(0), _mouseY(0), _restartGame(false), _quitGame(false), _highestScore(0)
{
	_font.loadFromFile(FONT_PATH);
	
	loadHighScore();

	_title = new Text("Game Over", _font, END_GAME_TEXT_SIZE);
	_options[0] = new Text("Restart", _font, END_GAME_OPTIONS_TEXT_SIZE);
	_options[1] = new Text("Quit", _font, END_GAME_OPTIONS_TEXT_SIZE);
	_youScoredText = new Text("You scored: 0", _font, END_GAME_SCORE_TEXT_SIZE);
	_highestScoreText = new Text("Highest Score: " + to_string(_highestScore), _font, END_GAME_SCORE_TEXT_SIZE);

	formatText(_title, SCREEN_WIDTH / 2 - _title->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 4 - _title->getGlobalBounds().height / 2, TEXT_COLOR_RED, Color::Red, true);
	formatText(_options[0], 32, SCREEN_HEIGHT - _options[0]->getGlobalBounds().height - 90,
		Color::White, TEXT_COLOR_BLUE, true);
	formatText(_options[1], SCREEN_WIDTH - _options[1]->getGlobalBounds().width - 32,
		SCREEN_HEIGHT - _options[1]->getGlobalBounds().height - 90, Color::White, Color::Red, true);
	formatText(_youScoredText, SCREEN_WIDTH / 2 - _youScoredText->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _youScoredText->getGlobalBounds().height / 2, Color::White, Color::Black, true);
	formatText(_highestScoreText, SCREEN_WIDTH / 2 - _highestScoreText->getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - _highestScoreText->getGlobalBounds().height / 2 + 64, Color::White, Color::Black, true);

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
	delete _youScoredText;
	delete _highestScoreText;
}

void EndGameState::show(Sprite& background, int& score)
{
	_window->setMouseCursorVisible(true);
	_background = background;

	_youScoredText->setString("You Scored: " + to_string(score));
	if (score > _highestScore)
	{
		_highestScore = score;
		_highestScoreText->setString("Highest Score: " + to_string(score));
		saveHighScore(_highestScore);
	}

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
			_restartGame = true;		
		else
			if (_selected[1])
				_quitGame = true;
		_clicked = false;
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
	_window->draw(*_youScoredText);
	_window->draw(*_highestScoreText);

	_window->display();
}

void EndGameState::saveHighScore(int& score)
{
	try
	{
		ofstream outputFile(SCORE_OUTPUT_PATH, ios::out | ios::binary);
		if (!outputFile.good())
			throw iostream::failure("Error opening the output file.");
		outputFile.write((char*)&score, sizeof(score));
		outputFile.close();
		if (outputFile.is_open())
			throw iostream::failure("Error closing the output file.");
	}
	catch (iostream::failure& exception)
	{
		cerr << "WARNING: " << exception.what() << endl;
	}
}

void EndGameState::loadHighScore()
{
	try
	{
		ifstream inputFile(SCORE_OUTPUT_PATH, ios::in | ios::binary);
		if (!inputFile.good())
			throw iostream::failure("No save files were found.");
		inputFile.read((char*)&_highestScore, sizeof(_highestScore));
		inputFile.close();
		if (inputFile.is_open())
			throw iostream::failure("Error closing the input file.");
	}
	catch (iostream::failure& exception)
	{
		cerr << "WARNING: " << exception.what() << endl;
	}
}