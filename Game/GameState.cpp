#include "GameState.h"

GameState::GameState(RenderWindow& window) : State(window)
{

}

GameState::~GameState()
{

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

}

void GameState::draw(float elapsed)
{
	_window->clear(Color::Black);
	_window->display();
}