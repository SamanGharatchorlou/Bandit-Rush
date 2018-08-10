#pragma once

#include "State.h"
#include "Game.h"
#include "MapDecoder.h"

#include <SFML/Graphics.hpp>

namespace srac
{
	class GameOverState : public State
	{
	private:
		gameDataRef _data;

		environment::MapDecoder* mapDecoder;
		sf::Sprite map;

		int _score;

		std::vector<int> scoreBoard;

		sf::Text scoreText;
		sf::Text highScoreText;

		sf::Sprite _play;

		void addnewScore();
		void updateScoreBoard();

	public:
		GameOverState(gameDataRef data, int score);

		void init();
		void preProcess() { }

		void handleInput();
		void update(float dt) { }
		void draw();

		void exit() { }
	};


}