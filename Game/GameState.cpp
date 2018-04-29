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
		}
}


void GameState::update(float elapsed)
{
	switch (_player->getCurrentState())
	{
		case Idle:
			cout << "Idle" << endl;
			break;
		case Moving:
			cout << "Moving" << endl;
			break;
		case Jumping:
			cout << "Jumping" << endl;
			break;
		case Falling:
			cout << "Falling" << endl;
			break;
	}

	_player->update(elapsed);
}

void GameState::draw(float elapsed)
{
	_window->clear({ 32, 64, 128, 255 });
	_window->draw(_player->getSprite());
	_window->display();
}