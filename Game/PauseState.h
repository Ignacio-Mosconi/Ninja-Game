#ifndef PAUSE_STATE
#define PAUSE_STATE

#include <SFML/Audio.hpp>
#include "State.h"

class PauseState : public State
{
private:
	Font _font;

	Text* _title;
	Text* _options[PAUSE_OPTIONS];

	SoundBuffer _selectBuffer;
	SoundBuffer _resumeBuffer;

	Sound _select;
	Sound _resume;

	bool _selected[PAUSE_OPTIONS];
	int _mouseX;
	int _mouseY;
	bool _clicked;
	bool _resumeGame;
	bool _quitGame;

protected:
	void input();
	void update(float elapsed);
	void draw() const;

public:
	PauseState(RenderWindow& window);
	~PauseState();

	void show();
	void resume();

	inline bool quitGame() { return _quitGame; }
	void setQuitGame(bool quitGame) { _quitGame = quitGame; }
};

#endif
