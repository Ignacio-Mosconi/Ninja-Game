#ifdef _DEBUG
#include <vld.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include "SplashState.h"
#include "MenuState.h"
#include "GameState.h"
#include "Definitions.h"
using namespace sf;

int main()
{
	VideoMode videoMode = VideoMode::getFullscreenModes()[4];
	RenderWindow window(videoMode, GAME_TITLE, Style::Fullscreen);
	State::setScreenDimensions(window.getSize());
	State::setScaleFactors(Vector2f((float)window.getSize().x / DEFAULT_WIDTH, (float)window.getSize().y / DEFAULT_HEIGHT));
	window.setMouseCursorVisible(false);
	window.clear();
	window.display();
	
	Image icon;
	Image cursorImage;
	Cursor cursor;

	icon.loadFromFile(WINDOW_ICON_PATH);
	cursorImage.loadFromFile(CURSOR_PATH);
	cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), Vector2u(2, 2));
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setMouseCursor(cursor);
	window.setFramerateLimit(FRAME_RATE);
	
	SplashState* splash = new SplashState(window, SPLASH_LOGO_PATH);
	MenuState* menu = new MenuState(window);
	GameState* game = new GameState(window);

	splash->start();
	
	while (window.isOpen())
	{
		if (!game->gameOver())
			menu->show();

		if (menu->startGame())
		{
			menu->setStartGame(false);
			game->restart();
		}
	}

	delete splash;
	delete menu;
	delete game;

	return 0;
}