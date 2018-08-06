#include "SplashScreenState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.h"

namespace srac
{
	SplashState::SplashState(gameDataRef data) : _data(data) {  }

	void SplashState::init()
	{
		_data->asset.loadTexture("splash screen", "Resources/Images/SplashScreen.png");

		splashScreen.setTexture(_data->asset.getTexture("splash screen"));
		_data->asset.fitToScreen(splashScreen, _data->window.getSize());
	}

	void SplashState::update(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > SPLASH_SCREEN_TIME)
		{
			_data->machine.replaceState(stateRef(new MainMenuState(_data)));
		}
	}

	void SplashState::handleInput() 
	{	  
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
		}
	}

	void SplashState::draw()
	{
		_data->window.clear();
		_data->window.draw(splashScreen);
		_data->window.display();
	}
}