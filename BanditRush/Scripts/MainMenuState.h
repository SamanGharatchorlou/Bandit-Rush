#pragma once
#include "State.h"
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace srac
{
	class MainMenuState : public State
	{
	private:
		gameDataRef _data;

		std::vector<sf::Sprite> _backgroundLayers;
		sf::Sprite _music;
		sf::Sprite _keyA, _keyD, _keySpace;
		sf::Sprite _arrowL, _arrowR, _arrowU, _arrowD;

		sf::Text _title, _pressKeys;
		sf::Text _textA, _textD, _textSpace;

		sf::Sound _gameMusic;

		sf::IntRect greyButton, greySpace;
		sf::Color grey;

		sf::Clock _clock;

		void initTitle();
		void initSound();

		void initInstructions();
		void drawInstructions();

		void greyKey(sf::Sprite& key);
		void greyText(sf::Text text);

	public:
		MainMenuState(gameDataRef data);

		void init();
		void preProcess() { }
		void handleInput();
		void update(float dt);
		void draw();

		void exit() { }
	};

}