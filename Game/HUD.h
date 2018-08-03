#ifndef HUD_H
#define HUD_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Definitions.h"
using namespace std;
using namespace sf;

enum Element
{
	Lives,
	Score,
	TimeLeft,
	HighestScore,
	FinalScore
};

class HUD
{
private:
	Font _font;

	Text* _lives;
	Text* _score;
	Text* _time;
	Text* _gameOver;
	Text* _restart;
	Text* _quit;
	Text* _youScored;
	Text* _highestScore;
	Text* _credits;

	SoundBuffer _clockTickBuffer;
	Sound _clockTick;

public:
	HUD();
	~HUD();

	void updateHUD(Element element, int number);
	void draw(RenderWindow* window, bool isGameOver);
};

#endif