#include <SFML/Graphics.hpp>
#include "SplashState.h"
#include "GameState.h"
#include "Definitions.h"
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game", Style::Titlebar | Style::Close);
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	SplashState* splash = new SplashState(window, SPLASH_LOGO_PATH);
	splash->start();

	GameState* game = new GameState(window);
	game->run();

	delete splash;
	delete game;
	return 0;
}