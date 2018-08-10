#pragma once

#include "StateMachine.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "EnemyController.h"
#include "DEFINITIONS.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

namespace srac
{
	class Player;

	struct GameData
	{
		sf::RenderWindow window;

		StateMachine machine;
		InputManager input;
		AssetManager asset;
		EnemyController enemyController;
		Player* player;
	};

	typedef std::shared_ptr<GameData> gameDataRef;

	class Game
	{
	private:
		gameDataRef _data = std::make_shared<GameData>();

		void runGame();

		float dt = 1.0f / MAX_FRAMERATE;

	public:
		Game(int windowWidth, int windowHeight, std::string title);

	};
}