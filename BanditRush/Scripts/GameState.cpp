#include "GameState.h"
#include "GameOverState.h"
#include "DEFINITIONS.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

namespace srac
{
	GameState::GameState(gameDataRef data) : _data(data) {  }

	void GameState::init()
	{
		sf::Window newWindow(sf::VideoMode(1024, 768), "drawing window");

		int pixleSize = 16;

		_mapDecoder = new environment::MapDecoder(_data->window, pixleSize);

		_mapDecoder->buildBackgroundLayers();
		_mapSprite = _mapDecoder->compressLayers();

		_gameController = new GameController(_data);

		_stats.loadStatScreen((_data->window));

		//load and play game sound
		//_gameMusic.setBuffer(_data->asset.getSoundBuffer("game sound"));
		//_gameMusic.play();
		//_gameMusic.setVolume(20);
		//_gameMusic.setLoop(true);

		// create player
		_data->player = new Player(_data);

		// create pool of enemies
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			_data->enemyController.addEnemy(_data, false);
		}

		_exit = false;
		frames = 0;
		frameCounter.restart();

		_spawnTime = 8.0f;
	}

	void GameState::exit()
	{
		_data->enemyController.clearEnemies();

		delete _mapDecoder;
		delete _gameController;
		delete _data->player;
	}


	void GameState::preProcess()
	{
		_data->player->processStateChanges();

		for (int i = 0; i < _data->enemyController.getAllEnemies().size(); i++)
		{
			_data->enemyController.getAllEnemy(i)->processStateChanges();
		}
	}


	void GameState::handleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}
		}

		_data->player->handleInput();

		for (int i = 0; i < _data->enemyController.getEnemies().size(); i++)
		{
			_data->enemyController.getEnemy(i)->handleInput();
		}
	}


	void GameState::update(float dt)
	{
		_data->player->update(dt);

		for (int i = 0; i < _data->enemyController.getEnemies().size(); i++)
		{
			_data->enemyController.getEnemy(i)->update(dt);
		}

		_spawnTime -= _data->player->getPlayerData()->attributes.getKills() / 5.0f;

		if (_spawnTime < 3.0f)
			_spawnTime = 3.0f;

		// spawn enemies
		if(_data->enemyController.getInactiveEnemies().size() > 0)
		{
			spawnEnemy(_spawnTime);
		}

		// arrow shower
		_gameController->showerLocation();
		_gameController->releaseArrows(3.0f, dt);

		if (_data->player->getPlayerData()->attributes.isDead())
		{
			_data->machine.replaceState(stateRef(new GameOverState(_data, _data->player->getPlayerData()->attributes.getKills())));
			_exit = true;
		}
	}


	void GameState::draw()
	{
		_data->window.clear();

		_data->window.draw(_mapSprite);

		_stats.drawHealth(_data->player->getPlayerData()->attributes.getHealth());
		_stats.drawKills(_data->player->getPlayerData()->attributes.getKills());

		for (int i = 0; i < _data->enemyController.getEnemies().size(); i++)
		{
			_data->enemyController.getEnemy(i)->draw();
		}

		_data->player->draw();

		_gameController->draw();

		_data->window.display();

		if (_exit)
		{
			exit();
		}

		//printFrameRate();
	}


	void GameState::spawnEnemy(float spawnTime)
	{
		// activate enemies
		if (_enemySpawn.getElapsedTime().asSeconds() > spawnTime)
		{
			_data->enemyController.getInactiveEnemy(0)->init(_data->player);

			_data->enemyController.activateEnemy(_data->enemyController.getInactiveEnemy(0));
			_enemySpawn.restart();
		}
	}


	void GameState::printFrameRate()
	{
		frames++;

		if (frameCounter.getElapsedTime().asSeconds() >= 1.0f)
		{
			std::cout << frames << std::endl;
			frames = 0;
			frameCounter.restart();
		}
	}
}