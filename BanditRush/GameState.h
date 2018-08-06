#pragma once
#include "State.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

#include "MapDecoder.h"
#include "StatScreen.h"
#include "GameController.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

namespace srac
{
	class GameState : public State
	{
	private:
		gameDataRef _data;

		environment::MapDecoder* _mapDecoder;
		environment::StatScreen _stats;

		GameController* _gameController;

		sf::Sprite _mapSprite;
		sf::Sound _gameMusic;

		sf::Clock _enemySpawn;
		sf::Clock _showerTimer;

		float _spawnTime;
		void spawnEnemy(float spawnTime);

		int frames;
		sf::Clock frameCounter;

		void printFrameRate();

		bool _exit;

	public:
		GameState(gameDataRef data);

		void init();
		void preProcess();
		void handleInput();
		void update(float dt);
		void draw();

		void exit();
	};
}
