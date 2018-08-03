#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"

class MenuState : public State
{
private:
	Font _font;

	Text* _title;
	Text* _options[MENU_OPTIONS];

	SoundBuffer _selectBuffer;

	Sound _select;

	bool _selected[MENU_OPTIONS];
	int _mouseX;
	int _mouseY;
	bool _clicked;
	bool _startGame;

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
