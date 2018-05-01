#include <SFML/Graphics.hpp>
#include "SplashState.h"
#include "MenuState.h"
#include "GameState.h"
#include "Definitions.h"
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ninja Thief", Style::Titlebar | Style::Close);
	window.setVerticalSyncEnabled(true);
	
	SplashState* splash = new SplashState(window, SPLASH_LOGO_PATH);
	splash->start();

	MenuState* menu = new MenuState(window);
	menu->show();

	GameState* game = new GameState(window);
	if (menu->startGame())
		game->run();

	delete splash;
	delete menu;
	delete game;
	return 0;
}