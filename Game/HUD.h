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
	Text* _restart;
	Text* _quit;

	void formatText(Text* text, int x, int y, Color fillColor, Color outlineColor = Color::White, bool outline = false);

public:
	HUD();
	~HUD();

	void updateHUD(Element element, int number);
	void draw(RenderWindow* window, bool isPaused, bool isGameOver);
};

#endif