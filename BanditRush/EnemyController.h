#pragma once
#include <vector>
#include <memory>

namespace srac
{
	class Enemy;
	class GameData;

	typedef std::vector<Enemy*> Enemies;
	typedef std::shared_ptr<GameData> gameDataRef;

	class EnemyController
	{
	private:
		Enemies _enemies;
		Enemies _activeEnemies;
		Enemies _inactiveEnemies;

	public:
		void addEnemy(gameDataRef data, bool active);
		void activateEnemy(Enemy* enemy);
		void deactivateEnemy(Enemy* enemy);

		void clearEnemies();

		// returns active and unactive enemies
		Enemy* getAllEnemy(int index);
		Enemies getAllEnemies();

		// returns only active enemies
		Enemy* getEnemy(int index);
		Enemies getEnemies();

		// returns only inactive enemies
		Enemy* getInactiveEnemy(int index);
		Enemies getInactiveEnemies();
	};
}