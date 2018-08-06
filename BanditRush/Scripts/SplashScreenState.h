#pragma once
#include "State.h"
#include "Game.h"

namespace srac 
{
	class SplashState : public State
	{
	private:
		gameDataRef _data;

		sf::Sprite splashScreen;

		sf::Clock _clock;

	public:
		SplashState(gameDataRef data);

		void init();
		void preProcess() { }
		void update(float dt);
		void handleInput();
		void draw();

		void exit() { }
	};
}