#include "GameState.h"
#include "Player.h"
#include "Fruit.h"
#include "Coin.h"
#include "Life.h"
#include "TimeBonus.h"
#include "Entity.h"
#include "HUD.h"
#include "PauseState.h"
#include "EndGameState.h"

GameState::GameState(RenderWindow& window) : State(window),
_gameOver(false), _score(0), _highestScore(0), _time(GAME_TIME), _timeSinceLastFrame(0)
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

	_pauseState = new PauseState(*_window);
	_endGameState = new EndGameState(*_window);

	_mainTheme.openFromFile(MAIN_THEME);
	_mainTheme.setLoop(true);

	_pauseBuffer.loadFromFile(PAUSE_SOUND);
	_pause.setBuffer(_pauseBuffer);
}

GameState::~GameState()
{
	delete _player;
	for (int i = 0; i < FRUITS; i++)
		delete _fruits[i];
	for (int i = 0; i < COINS; i++)
		delete _coins[i];
	delete _life;
	delete _timeBonus;

	delete _ground;
	delete _sky;

	delete _hud;
	delete _pauseState;
	delete _endGameState;
}

void GameState::run()
{
	if (_mainTheme.getStatus() == SoundSource::Status::Stopped)
		_mainTheme.play();

	while (!_gameOver && !_pauseState->quitGame() && _window->isOpen())
	{
		float elapsed = _clock->restart().asSeconds();

		input();
		if (!_pauseState->quitGame())
		{
			update(elapsed);
			draw();
		}
	}
	if (!_pauseState->quitGame())
	{
		result();
		if (!_endGameState->quitGame())
			restart();
		else
		{
			_endGameState->setQuitGame(false);
			_gameOver = false;
		}
	}
	else
	{
		_mainTheme.stop();
		_pauseState->setQuitGame(false);
	}
}

void GameState::input()
{
	Event event;

	if (_window->pollEvent(event))
	{
		if (!_gameOver)
		{
			bool wasPaused = false;

			switch (event.type)
			{
				case Event::Closed:
					_window->close();
					break;
				case Event::KeyPressed:
					if (event.key.code == Keyboard::ESCAPE_KEY)
						pause(wasPaused);
					break;
				case Event::JoystickButtonPressed:
					if (event.joystickButton.button == PAUSE_BUTTON)
						pause(wasPaused);
					break;
			}
			if (wasPaused && !_pauseState->quitGame())
			{
				_mainTheme.play();
				_clock->restart();
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
		fruitPlayerCollision(_fruits[i], _player);
		fruitGroundCollision(_fruits[i]);
	}
	for (int i = 0; i < COINS; i++)
	{
		_coins[i]->update(elapsed);
		coinPlayerCollision(_coins[i], _player);
	}
	if (_player->getLives() < PLAYER_LIVES)
	{
		_life->update(elapsed);
		lifePlayerCollision(_life, _player);
	}
	_timeBonus->update(elapsed);
	timeBonusPlayerCollision(_timeBonus, _player);
}

void GameState::draw() const
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

	_hud->draw(_window);

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

void GameState::fruitGroundCollision(Fruit* f)
{
	if (f->hasReachedBottom())
	{
		switch (f->getKind())
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
		f->setHasReachedBottom(false);
		_hud->updateHUD(Score, _score);
	}
}

void GameState::pause(bool& wasPaused)
{
	Texture backgroundTexture;
	Sprite background;

	backgroundTexture.create(_window->getSize().x, _window->getSize().y);
	backgroundTexture.update(*_window);
	background.setTexture(backgroundTexture);

	wasPaused = true;
	_mainTheme.pause();
	_pause.play();
	_pauseState->show(background);
}

void GameState::result()
{
	Texture backgroundTexture;
	Sprite background;

	backgroundTexture.create(_window->getSize().x, _window->getSize().y);
	backgroundTexture.update(*_window);
	background.setTexture(backgroundTexture);

	_mainTheme.stop();
	_pause.play();
	_endGameState->show(background);
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
	_score = 0;
	_time = GAME_TIME;
	_timeSinceLastFrame = 0;

	_hud->updateHUD(Lives, _player->getLives());
	_hud->updateHUD(Score, _score);
	_hud->updateHUD(TimeLeft, _time);

	_clock->restart();
	run();
}