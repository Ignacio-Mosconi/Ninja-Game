#include "GameState.h"

GameState::GameState(RenderWindow& window) : State(window)
{
	srand(time(0));

	_player = new Player(SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, SCREEN_HEIGHT - (GROUND_HEIGHT + PLAYER_HEIGHT), PLAYER_PATH);
	for (int i = 0; i < FRUITS; i++)
		_fruits[i] = new Fruit(rand() % (FRUIT_MAX_X - FRUIT_MIN_X - FRUIT_WIDTH) + FRUIT_MIN_X, FRUIT_MIN_Y, FRUIT_PATH);
	_ground = new Entity(0, SCREEN_HEIGHT - GROUND_HEIGHT, GROUND_PATH);
	for (int i = 0; i < COINS; i++)
		_coins[i] = new Coin(rand() % (COLLECTIBLE_MAX_X - COLLECTIBLE_MIN_X - COIN_WIDTH) + COLLECTIBLE_MIN_X,
			rand() % (COLLECTIBLE_MAX_Y - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y, COIN_PATH);
	_life = new Life(rand() % (COLLECTIBLE_MAX_X - COLLECTIBLE_MIN_X - COIN_WIDTH) + COLLECTIBLE_MIN_X,
		rand() % (COLLECTIBLE_MAX_Y - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y, LIFE_PATH);

	_hud = new HUD();

	_gameOver = false;
	_paused = false;
	_score = 0;

	_deltaTime = 0;
}

GameState::~GameState()
{
	delete _player;
	for (int i = 0; i < FRUITS; i++)
		delete _fruits[i];
	delete _ground;
	for (int i = 0; i < COINS; i++)
		delete _coins[i];
	delete _life;

	delete _hud;
}

void GameState::run()
{
	while (!_gameOver &&_window->isOpen())
	{
		float elapsed = _clock->restart().asSeconds();

		if (!_paused)
		{
			input();
			update(elapsed);
			draw(elapsed);
		}
		else
		{
			input();
			draw(elapsed);
		}
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
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
				{
					if (!_paused)
						pause();
					else
						resume();
				}
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
	for (int i = 0; i < COINS; i++)
		_coins[i]->update(elapsed);
	if (_player->getLives() < PLAYER_LIVES)
		_life->update(elapsed);

	for (int i = 0; i < FRUITS; i++)
		fruitPlayerCollision(_fruits[i], _player);
	for (int i = 0; i < COINS; i++)
		coinPlayerCollision(_coins[i], _player);
	lifePlayerCollision(_life, _player);
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
		for (int i = 0; i < COINS; i++)
			_window->draw(_coins[i]->getSprite());
		_window->draw(_life->getSprite());

		_hud->draw(_window, _paused, _gameOver);

		_window->display();
	}
}

void GameState::fruitPlayerCollision(Fruit* f, Player* p)
{
	if (f->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()) && f->isEnabled())
	{
		f->disable();
		if (p->getLives() > 1)
		{
			p->die();
			_hud->updateHUD(Lives, p->getLives());
		}
		else
			_gameOver = true;
	}
}

void GameState::coinPlayerCollision(Coin* c, Player* p)
{
	if (c->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()) && c->isEnabled())
	{
		c->disable();
		_score += COIN_SCORE;
		_hud->updateHUD(Score, _score);
	}
}

void GameState::lifePlayerCollision(Life* l, Player* p)
{
	if (l->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()) && l->isEnabled())
	{
		l->disable();
		p->setLives(p->getLives() + 1);
		_hud->updateHUD(Lives, p->getLives());
	}
}

void GameState::pause()
{
	_paused = true;
}

void GameState::resume()
{
	_paused = false;
}