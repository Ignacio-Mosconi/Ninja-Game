#include "GameState.h"

GameState::GameState(RenderWindow& window) : State(window)
{
	srand(time(0));

	_player = new Player(SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, SCREEN_HEIGHT - (GROUND_HEIGHT + PLAYER_HEIGHT), PLAYER_PATH);
	for (int i = 0; i < FRUITS; i++)
		_fruits[i] = new Fruit(rand() % (FRUIT_MAX_X - FRUIT_MIN_X - FRUIT_WIDTH) + FRUIT_MIN_X, FRUIT_MIN_Y, FRUIT_PATH);
	for (int i = 0; i < COINS; i++)
		_coins[i] = new Coin(rand() % (COLLECTIBLE_MAX_X - COLLECTIBLE_MIN_X - COIN_WIDTH) + COLLECTIBLE_MIN_X,
			rand() % (COLLECTIBLE_MAX_Y - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y, COIN_PATH);
	_life = new Life(rand() % (COLLECTIBLE_MAX_X - COLLECTIBLE_MIN_X - LIFE_WIDTH) + COLLECTIBLE_MIN_X,
		rand() % (COLLECTIBLE_MAX_Y - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y, LIFE_PATH);
	_timeBonus = new TimeBonus(rand() % (COLLECTIBLE_MAX_X - COLLECTIBLE_MIN_X - TIME_BONUS_WIDTH) + COLLECTIBLE_MIN_X,
		rand() % (COLLECTIBLE_MAX_Y - COLLECTIBLE_MIN_Y) + COLLECTIBLE_MIN_Y, TIME_BONUS_PATH);
	
	_ground = new Entity(0, SCREEN_HEIGHT - GROUND_HEIGHT, GROUND_PATH);
	_sky = new Entity(0, 0, SKY_PATH);
	
	_hud = new HUD();

	_mainTheme.openFromFile(MAIN_THEME);
	_mainTheme.setLoop(true);

	_gameOver = false;
	_paused = false;
	_score = 0;
	_highestScore = 0;
	_time = GAME_TIME;
	_timeSinceLastFrame = 0;
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
	delete _timeBonus;

	delete _hud;
}

void GameState::run()
{
	if (_mainTheme.getStatus() == SoundSource::Status::Stopped)
		_mainTheme.play();

	while (!_gameOver && _window->isOpen())
	{
		float elapsed = _clock->restart().asSeconds();
		if (!_paused)
		{
			input();
			update(elapsed);
			draw();
		}
		else
		{
			input();
			draw();
		}
	}
	result();
}

void GameState::input()
{
	Event event;

	if (_window->pollEvent(event))
	{
		if (!_gameOver)
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
		else
			switch (event.type)
			{
				case Event::Closed:
					_window->close();
					break;
				case Event::KeyPressed:
					switch (event.key.code)
					{
						case Keyboard::Escape:
							_gameOver = false;
							break;
						case Keyboard::Return:
							restart();
							break;
					}
			}
	}
}

void GameState::update(float elapsed)
{
	_time -= elapsed;
	_timeSinceLastFrame += elapsed;
	if (_timeSinceLastFrame >= 1)
	{
		_hud->updateHUD(TimeLeft, int(_time));
		_timeSinceLastFrame = 0;
	}
	if (_time <= 0)
		_gameOver = true;

	_player->update(elapsed);
	for (int i = 0; i < FRUITS; i++)
	{
		_fruits[i]->update(elapsed);
		if (_fruits[i]->hasReachedBottom())
		{
			switch (_fruits[i]->getKind())
			{
				case Watermelon:
					_score += WATERMELON_SCORE;
					break;
				case Apple:
					_score += APPLE_SCORE;
					break;
				case Pear:
					_score += PEAR_SCORE;
					break;
				case Banana:
					_score += BANANA_SCORE;
					break;
			}
			_fruits[i]->setHasReachedBottom(false);
			_hud->updateHUD(Score, _score);
		}
	}
	for (int i = 0; i < COINS; i++)
		_coins[i]->update(elapsed);
	if (_player->getLives() < PLAYER_LIVES)
		_life->update(elapsed);
	_timeBonus->update(elapsed);

	for (int i = 0; i < FRUITS; i++)
		fruitPlayerCollision(_fruits[i], _player);
	for (int i = 0; i < COINS; i++)
		coinPlayerCollision(_coins[i], _player);
	lifePlayerCollision(_life, _player);
	timeBonusPlayerCollision(_timeBonus, _player);
}

void GameState::draw()
{
	_window->clear();
	
	_window->draw(_sky->getSprite());
	_window->draw(_ground->getSprite());

	_window->draw(_player->getSprite());
	for (int i = 0; i < FRUITS; i++)
		_window->draw(_fruits[i]->getSprite());
	for (int i = 0; i < COINS; i++)
		_window->draw(_coins[i]->getSprite());
	_window->draw(_life->getSprite());
	_window->draw(_timeBonus->getSprite());

	_hud->draw(_window, _paused, _gameOver);

	_window->display();
}

void GameState::fruitPlayerCollision(Fruit* f, Player* p)
{
	if (f->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()) && f->isEnabled() && !p->isFlickering())
	{
		f->disable();
		p->die();
		_hud->updateHUD(Lives, p->getLives());
		if (p->getLives() == 0)
			_gameOver = true;
	}
}

void GameState::coinPlayerCollision(Coin* c, Player* p)
{
	if (c->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()) && c->isEnabled())
	{
		if (p->pickUpItem(Coins))
		{
			c->disable();
			_score += COIN_SCORE;
			_hud->updateHUD(Score, _score);
		}
	}
}

void GameState::lifePlayerCollision(Life* l, Player* p)
{
	if (l->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()) && l->isEnabled())
	{
		if (p->pickUpItem(LifeBonuses))
		{
			l->disable();
			_hud->updateHUD(Lives, p->getLives());
		}
	}
}

void GameState::timeBonusPlayerCollision(TimeBonus* t, Player* p)
{
	if (t->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()) && t->isEnabled())
	{
		if (p->pickUpItem(TimeBonuses))
		{
			t->disable();
			_time += TIME_BONUS_TIME;
		}
	}
}

void GameState::pause()
{
	_mainTheme.pause();
	_paused = true;
}

void GameState::resume()
{
	_mainTheme.play();
	_paused = false;
}

void GameState::result()
{
	_mainTheme.stop();

	_hud->updateHUD(FinalScore, _score);
	if (_score > _highestScore)
	{
		_highestScore = _score;
		_hud->updateHUD(HighestScore, _highestScore);
	}

	while (_gameOver && _window->isOpen())
	{
		float elapsed = _clock->restart().asSeconds();

		input();
		draw();
	}
}

void GameState::restart()
{
	_player->respawn();
	_player->setLives(PLAYER_LIVES);
	_player->setIsInvincible(false);

	for (int i = 0; i < FRUITS; i++)
	{
		_fruits[i]->respawn();
		_fruits[i]->disable();
	}
	for (int i = 0; i < COINS; i++)
	{
		_coins[i]->respawn();
		_coins[i]->disable();
	}
	_life->respawn();
	_life->disable();
	_timeBonus->respawn();
	_timeBonus->disable();

	_gameOver = false;
	_paused = false;
	_score = 0;
	_time = GAME_TIME;
	_timeSinceLastFrame = 0;

	_hud->updateHUD(Lives, _player->getLives());
	_hud->updateHUD(Score, _score);
	_hud->updateHUD(TimeLeft, _time);

	run();
}