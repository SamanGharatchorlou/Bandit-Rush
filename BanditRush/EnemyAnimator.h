#pragma once
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

namespace srac
{
	class EnemyAnimator
	{
	private:
		gameDataRef _data;

		sf::IntRect _activeClip;
		sf::Texture _spriteSheet;

		std::map<std::string, std::vector<int>> _animationCode;

		int _xCount, _yCount;
		int _spriteWidth, _spriteHeight;
		int _startingIndex, _clipCount, _animationIndex;
		int _direction;

		void loadSpriteSheet();
		void configureAnimations();
		void nextClip();

		sf::Clock _clipTimer;
		sf::Clock _animationTimer;

		bool _stopped;

	public:
		EnemyAnimator();

		sf::Texture& getSpriteSheet();
		sf::IntRect getActiveClip();

		void playLoop(float speed);
		bool playSingle(float speed);
		bool partComplete(float speed, float percentComplete);

		void newAnimation(std::string name);
		void spriteDimentions(int xCount, int yCount);

		void resetClock();

	};
}
