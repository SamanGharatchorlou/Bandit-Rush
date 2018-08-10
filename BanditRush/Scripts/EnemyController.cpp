#include "EnemyController.h"
#include "Enemy.h"
#include <memory>
#include <vector>
#include <iostream>

namespace srac
{
	void EnemyController::addEnemy(gameDataRef data, bool active)
	{
		Enemy* enemy = new Enemy(data);

		_enemies.push_back(enemy);

		if (active)
			activateEnemy(enemy);
		else
			deactivateEnemy(enemy);
	}

	void EnemyController::clearEnemies()
	{
		for (int i = 0; i < _enemies.size(); i++)
		{
			delete _enemies[i];
		}

		_enemies.clear();
		_activeEnemies.clear();
		_inactiveEnemies.clear();
	}

	void EnemyController::activateEnemy(Enemy* enemy)
	{
		Enemies::iterator iter = std::find(_inactiveEnemies.begin(), _inactiveEnemies.end(), enemy);

		if (iter != _inactiveEnemies.end())
		{
			_inactiveEnemies.erase(iter);
		}

		_activeEnemies.push_back(enemy);
	}

	void EnemyController::deactivateEnemy(Enemy* enemy)
	{
		Enemies::iterator iter = std::find(_activeEnemies.begin(), _activeEnemies.end(), enemy);

		if (iter != _activeEnemies.end())
		{
			_activeEnemies.erase(iter);
		}

		_inactiveEnemies.push_back(enemy);
	}


	Enemy* EnemyController::getAllEnemy(int index)
	{
		return _enemies[index];
	}

	Enemies EnemyController::getAllEnemies()
	{
		return _enemies;
	}


	Enemy* EnemyController::getEnemy(int index)
	{
		return _activeEnemies[index];
	}

	Enemies EnemyController::getEnemies()
	{
		return _activeEnemies;
	}

	Enemy* EnemyController::getInactiveEnemy(int index)
	{
		return _inactiveEnemies[index];
	}

	Enemies EnemyController::getInactiveEnemies()
	{
		return _inactiveEnemies;
	}
}