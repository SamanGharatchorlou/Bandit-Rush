#include "EnemyDeadState.h"
#include "Player.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	EnemyDeadState::EnemyDeadState(gameDataRef data, enemyDataRef enemyData) : _data(data), _enemy(enemyData) {	}

	void EnemyDeadState::init()
	{
		// start hurt animation
		initAnimation("die");

		// set origin, scale & position
		initSprite();

		// init variables
		_enemy->attributes.setTakingDmg(false);

		_data->player->getPlayerData()->attributes.addKill();
	}


	void EnemyDeadState::update(float dt)
	{
		if (_enemy->animator.playSingle(6.0f))
		{
			recycleDead();
		}

		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyDeadState::draw()
	{
		_data->window.draw(_sprite);
	}


	// --- Private Functions ---

	void EnemyDeadState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width * ENEMY_CENTER, _sprite.getGlobalBounds().height);
		_sprite.setScale(ENEMY_SCALE * _enemy->attributes.getDirection(), ENEMY_SCALE);
		_sprite.setPosition(_enemy->attributes.getPosition());
	}

	void EnemyDeadState::initAnimation(std::string animation)
	{
		_enemy->animator.newAnimation(animation);
		_sprite.setTexture(_enemy->animator.getSpriteSheet());
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyDeadState::recycleDead()
	{
		for (int i = 0; i < _data->enemyController.getEnemies().size(); i++)
		{
			if (_data->enemyController.getEnemy(i)->getEnemyData()->attributes.isDead() &&
				_data->enemyController.getEnemy(i)->getEnemyData()->attributes.getPosition() == _enemy->attributes.getPosition())
			{
				_data->enemyController.deactivateEnemy(_data->enemyController.getEnemy(i));
			}
		}
	}

}