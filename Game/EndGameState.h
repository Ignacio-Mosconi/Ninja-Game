#ifndef END_GAME_STATE_H
#define END_GAME_STATE_H

#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include "State.h"

class EndGameState : public State
{
private:
	Font _font;

	Text* _title;
	Text* _options[END_GAME_OPTIONS];
	Text* _youScoredText;
	Text* _highestScoreText;

	SoundBuffer _selectBuffer;

	Sound _select;

	Sprite _background;
	RectangleShape _alphaRect;

	bool _selected[END_GAME_OPTIONS];
	int _mouseX;
	int _mouseY;
	bool _clicked;
	bool _restartGame;
	bool _quitGame;
	
	int _highestScore;

	void saveHighScore(int& score);
	void loadHighScore();

protected:
	void input();
	void update(float elapsed);
	void draw() const;

public:
	EndGameState(RenderWindow& window);
	~EndGameState();

	void show(Sprite& background, int& score);
	void restart();

	inline bool quitGame() { return _quitGame; }
	void setQuitGame(bool quitGame) { _quitGame = quitGame; }
	int getHighestScore() { return _highestScore; }
};

#endif
