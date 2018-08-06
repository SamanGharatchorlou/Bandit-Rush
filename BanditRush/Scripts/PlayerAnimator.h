#pragma once
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

namespace srac
{
	class PlayerAnimator
	{
	private:
		gameDataRef _data;

		sf::IntRect _activeClip;
		sf::Texture _spriteSheet;

		std::map<std::string, std::vector<int>> _animationCode;
		std::map<std::string, sf::Texture> _spriteSheets;

		int _xCount, _yCount;
		int _spriteWidth, _spriteHeight;
		int _startingIndex, _clipCount, _animationIndex;
		int _direction;

		void loadSpriteSheet(std::string name, std::string filePath);
		void configureAnimations();
		void nextClip();

		sf::Clock _clipTimer;
		sf::Clock _animationTimer;

		bool _stopped;

		void sheetDimentions(int xCount, int yCount);

	public:
		PlayerAnimator();

		sf::Texture& getSpriteSheet();
		sf::IntRect getActiveClip();

		void playLoop(float speed);
		bool playSingle(float speed);
		bool partComplete(float speed, float percentComplete);

		void activateSheetFor(std::string animationName);
		void newAnimation(std::string name);

		//NOTE: NOT USED
		void resetClock();
	};
}
