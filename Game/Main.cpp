#ifdef _DEBUG
#include <vld.h>
#endif

#include <SFML/Graphics.hpp>
#include "SplashState.h"
#include "MenuState.h"
#include "GameState.h"
#include "Definitions.h"
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ninja Thief", Style::Titlebar | Style::Close);
	Image icon;
	icon.loadFromFile(WINDOW_ICON_PATH);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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