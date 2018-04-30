#ifndef HUD_H
#define HUD_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Definitions.h"
using namespace std;
using namespace sf;

enum Element
{
	Lives,
	Score
};

class HUD
{
private:
	Font _font;

	Text* _lives;
	Text* _score;
	Text* _paused;
	Text* _gameOver;

	void formatText(Text* text, int x, int y, Color fillColor, Color outlineColor, bool outline);

public:
	HUD();
	~HUD();

	void updateHUD(Element element, int number);
	void draw(RenderWindow* window, bool isPaused, bool isGameOver);
};

#endif