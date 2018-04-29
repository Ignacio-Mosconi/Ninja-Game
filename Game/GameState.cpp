#include "GameState.h"

GameState::GameState(RenderWindow& window) : State(window)
{
	_player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - (GROUND_HEIGHT + PLAYER_HEIGHT), PLAYER_PATH);
}

GameState::~GameState()
{
	delete _player;
}

void GameState::run()
{
	while (!gameOver &&_window->isOpen())
	{
		float elapsed = _clock->restart().asSeconds();

		input();
		update(elapsed);
		draw(elapsed);
	}
}

void GameState::input()
{
	Event event;

	if (_window->pollEvent(event))
		switch (event.type)
		{
		case Event::Closed:
			_window->close();
			break;
		case Event::KeyReleased:
			switch (Event::KeyReleased)
			{
				case Keyboard::Left | Keyboard::Right:
					if (_player->getCurrentState() == Moving)
						_player->setCurrentState(Idle);
					break;
			}
		}
}

void GameState::update(float elapsed)
{
	_player->update(elapsed);
}

void GameState::draw(float elapsed)
{
	_window->clear(Color::White);
	_window->draw(_player->getSprite());
	_window->display();
}