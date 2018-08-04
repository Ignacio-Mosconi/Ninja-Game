#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"

enum MenuScreen
{
	Main,
	Credits
};

class MenuState : public State
{
private:
	Font _font;

	Text* _title;
	Text* _options[MENU_OPTIONS];

	Text* _creditsTitle;
	Text* _creditsOptions[CREDITS_OPTIONS];
	Text* _credits[CREDITS_ITEMS];
	Text* _names[CREDITS_ITEMS];
	Text* _poweredBySFML;

	SoundBuffer _selectBuffer;

	Sound _select;

	bool _selected[MENU_OPTIONS];
	bool _creditsSelected[CREDITS_OPTIONS];
	int _mouseX;
	int _mouseY;
	bool _clicked;
	bool _startGame;
	MenuScreen _currentScreen;

protected:
	void input();
	void update(float elapsed);
	void draw() const;

public:
	MenuState(RenderWindow& window);
	~MenuState();

	void show();

	inline bool startGame() { return _startGame; }
	void setStartGame(bool start) { _startGame = start; }
};

#endif
