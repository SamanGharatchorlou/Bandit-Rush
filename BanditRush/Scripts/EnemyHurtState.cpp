#include "EnemyHurtState.h"
#include "EnemyDeadState.h"
#include "EnemyIdleState.h"
#include "EnemyAttackState.h"
#include "Player.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	EnemyHurtState::EnemyHurtState(gameDataRef data, enemyDataRef enemyData) : _data(data), _enemy(enemyData) {	}

	void EnemyHurtState::init()
	{
		// start hurt animation
		initAnimation("hurt");

		// set origin, scale & position
		initSprite();

		// init variables
		_enemy->attributes.setTakingDmg(false);
	}

	void EnemyHurtState::update(float dt)
	{
		// DIE
		if (_enemy->attributes.isDead())
		{
			toDeadState();
		}
		// HIT: interruption, restart state
		else if (_enemy->attributes.getTakingDmg())
		{
			toHurtState();
		}
		// resume previous state
		else if (_enemy->animator.playSingle(5.0f))
		{
			facePlayer();
			_enemy->machine.removeState();
		}

		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyHurtState::draw()
	{
		_data->window.draw(_sprite);
	}


	// --- Private Functions ---

	void EnemyHurtState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width * ENEMY_CENTER, _sprite.getGlobalBounds().height);
		_sprite.setScale(ENEMY_SCALE * _enemy->attributes.getDirection(), ENEMY_SCALE);
		_sprite.setPosition(_enemy->attributes.getPosition());
	}

	void EnemyHurtState::initAnimation(std::string animation)
	{
		_enemy->animator.newAnimation(animation);
		_sprite.setTexture(_enemy->animator.getSpriteSheet());
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyHurtState::facePlayer()
	{
		if (_data->player->getPlayerData()->attributes.getPosition().x < _enemy->attributes.getPosition().x)
			_enemy->attributes.setDirection(1);
		else
			_enemy->attributes.setDirection(-1);
	}

	void EnemyHurtState::toHurtState()
	{
		_enemy->machine.replaceState(stateRef(new EnemyHurtState(_data, _enemy)));
	}

	void EnemyHurtState::toDeadState()
	{
		_enemy->machine.replaceState(stateRef(new EnemyDeadState(_data, _enemy)));
	}
}