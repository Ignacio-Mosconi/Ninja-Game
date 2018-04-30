#include "GameState.h"

GameState::GameState(RenderWindow& window) : State(window)
{
	srand(time(0));
	_player = new Player(SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, SCREEN_HEIGHT - (GROUND_HEIGHT + PLAYER_HEIGHT), PLAYER_PATH);
	for (int i = 0; i < FRUITS; i++)
		_fruits[i] = new Fruit(rand() % (FRUIT_MAX_X - FRUIT_MIN_X) + FRUIT_MIN_X, FRUIT_MIN_Y, FRUIT_PATH);
	_ground = new Entity(0, SCREEN_HEIGHT - GROUND_HEIGHT, GROUND_PATH);

	_gameOver = false;
	_deltaTime = 0;
}

GameState::~GameState()
{
	delete _player;
	for (int i = 0; i < FRUITS; i++)
		delete _fruits[i];
	delete _ground;
}

void GameState::run()
{
	while (!_gameOver &&_window->isOpen())
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
	for (int i = 0; i < FRUITS; i++)
		_fruits[i]->update(elapsed);

	for (int i = 0; i < FRUITS; i++)
		fruitPlayerCollision(_fruits[i], _player);
}

void GameState::draw(float elapsed)
{
	_deltaTime += elapsed;

	if (_deltaTime >= _drawFrameTime)
	{
		_deltaTime = 0;
		_window->clear({ 32, 64, 128, 255 });

		_window->draw(_player->getSprite());
		for (int i = 0; i < FRUITS; i++)
			_window->draw(_fruits[i]->getSprite());
		_window->draw(_ground->getSprite());

		_window->display();
	}

}

void GameState::fruitPlayerCollision(Fruit* f, Player* p)
{
	if (f->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()) && f->isEnabled())
	{
		f->disable();
		if (p->getLives() > 1)
			p->die();
		else
			_gameOver = true;
	}
}