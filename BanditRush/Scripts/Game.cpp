#include "Game.h"
#include "SplashScreenState.h"

namespace srac
{
	Game::Game(int windowWidth, int windoeHeight, std::string title)
	{
		_data->window.create(sf::VideoMode(windowWidth, windoeHeight), title, sf::Style::Close | sf::Style::Titlebar);
		_data->window.setFramerateLimit(MAX_FRAMERATE);

		_data->machine.addState(stateRef(new SplashState(_data)));

		runGame();
	}

	void Game::runGame()
	{
		while (_data->window.isOpen())
		{
			_data->machine.processStateChanges();

			_data->machine.getActiveState()->preProcess();
			_data->machine.getActiveState()->handleInput();
			_data->machine.getActiveState()->update(dt);
			_data->machine.getActiveState()->draw();
		}
	}
}