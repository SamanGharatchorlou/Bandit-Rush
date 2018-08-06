#pragma once
#include "Game.h"
#include "ArrowShower.h"
#include "DEFINITIONS.h"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace srac
{
	class GameController
	{
	private:
		gameDataRef _data;

		ArrowShower* arrowShower;

		sf::Font font;
		sf::Text warningText;

		sf::Clock showerTimer;

		bool levelChosen;

		float warningTime;
		float showerTime;
		float fallTime;
		float showerCooldown;

		bool _hasHit;
		bool _flashing;

		int _changeRate;
		int _flashDirection;

		void flashWarning();
		void warningPosition();
		void resetWarning();

		void checkArrowHit();

	public:
		GameController(gameDataRef data);

		void showerLocation();
		void prepareShower(int level);
		void releaseArrows(float time, float dt);

		void draw();
	};
}