#include "Enemy.h"
#include "EnemyIdleState.h"
#include "GameController.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	Enemy::Enemy(gameDataRef data) : _data(data)
	{
		_enemy->machine.addState(stateRef(new EnemyIdleState(_data, _enemy)));
		_enemy->attributes.setSize(sf::Vector2f(ENEMY_WIDTH, ENEMY_HEIGHT));
	}

	void Enemy::init(Player* player)
	{
		srand(time(NULL));

		_enemy->machine.clearStates();
		_enemy->machine.replaceState(stateRef(new EnemyIdleState(_data, _enemy)));

		float level = _enemy->attributes.getLevel(rand() % 3);

		_enemy->attributes.setBoundary(level);
		_enemy->attributes.setPosition(level);
		_enemy->attributes.setDirection(1);

		_enemy->attributes.initRandHealth((((rand() % 100) - 50) / 100.0f) + 1.0f);
		_enemy->attributes.setRandHealth(ENEMY_HEALTH);
		_enemy->attributes.alive();

		// random attributes 50% - 100% of base level
		_enemy->attributes.initRandSpeed((((rand() % 100) - 50) / 100.0f) + 1.0f);
	}

	void Enemy::processStateChanges()
	{
		_enemy->machine.processStateChanges();
	}

	void Enemy::handleInput()
	{
		_enemy->machine.getActiveState()->handleInput();
	}

	void Enemy::update(float dt)
	{
		_enemy->machine.getActiveState()->update(dt);
	}

	void Enemy::draw()
	{
		_enemy->machine.getActiveState()->draw();
	}

	enemyDataRef Enemy::getEnemyData()
	{
		return _enemy;
	}
}