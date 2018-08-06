#include "EnemyIdleState.h"
#include "EnemyRunState.h"
#include "EnemyHurtState.h"
#include "EnemyAttackState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	EnemyIdleState::EnemyIdleState(gameDataRef data, enemyDataRef enemyData) : _data(data), _enemy(enemyData) {	}

	void EnemyIdleState::init()
	{
		// start idle animation
		initAnimation("idle");

		// set origin, scale & position
		initSprite();

		// init variables
		_enemy->attributes.setTakingDmg(false);
	}

	void EnemyIdleState::update(float dt)
	{
		// ATTACK
		if (_enemy->attributes.canAttack() && isPlayerInRange(ENEMY_ATTACK_RANGE))
		{
			toAttackState();
		}
		// HURT
		else if (_enemy->attributes.getTakingDmg())
		{
			toHurtState();
		}
		// RUN
		else if (!isNearPlayer() && inBoundary())
		{
			toRunState();
		}
		// IDLE
		else
		{
			facePlayer();
			beIdle();
		}
	}

	void EnemyIdleState::draw()
	{
		_data->window.draw(_sprite);
	}

	void EnemyIdleState::resume()
	{
		_enemy->animator.newAnimation("idle");
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}


	// --- Private Functions ---

	void EnemyIdleState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width * ENEMY_CENTER, _sprite.getGlobalBounds().height);
		_sprite.setScale(ENEMY_SCALE * _enemy->attributes.getDirection(), ENEMY_SCALE);
		_sprite.setPosition(_enemy->attributes.getPosition());
	}

	void EnemyIdleState::initAnimation(std::string animation)
	{
		_enemy->animator.newAnimation(animation);
		_sprite.setTexture(_enemy->animator.getSpriteSheet());
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyIdleState::toAttackState()
	{
		_enemy->machine.addState(stateRef(new EnemyAttackState(_data, _enemy)));
	}

	void EnemyIdleState::toHurtState()
	{
		_enemy->machine.addState(stateRef(new EnemyHurtState(_data, _enemy)));
	}

	void EnemyIdleState::toRunState()
	{
		_enemy->machine.replaceState(stateRef(new EnemyRunState(_data, _enemy)));
	}

	void EnemyIdleState::beIdle()
	{
		_sprite.setScale(ENEMY_SCALE * _enemy->attributes.getDirection(), ENEMY_SCALE);

		_enemy->animator.playLoop(6.0f);
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	bool EnemyIdleState::isPlayerInRange(float range)
	{
		sf::Vector2f playerPos = _data->player->getPlayerData()->attributes.getPosition();
		sf::Vector2f playerSize = _data->player->getPlayerData()->attributes.getSize();

		// adjust enemy attack collision box depending on direction
		int enemyDir = _enemy->attributes.getDirection() == 1 ? 1 : 0;

		sf::Vector2f enemyPos = sf::Vector2f(
			_enemy->attributes.getPosition().x - (enemyDir * range),
			_enemy->attributes.getPosition().y - range);

		sf::IntRect enemyAttackBox = _collider.getBox(enemyPos, range);
		sf::IntRect playerBoxCollider = _collider.getBoxCollider(playerPos, playerSize);

		if (enemyAttackBox.intersects(playerBoxCollider))
		{
			return true;
		}
		else
			return false;
	}

	bool EnemyIdleState::inBoundary()
	{
		if ((_enemy->attributes.getPosition().x < _enemy->attributes.getBoundary()[0] && _enemy->attributes.getDirection() == 1) ||
			(_enemy->attributes.getPosition().x > _enemy->attributes.getBoundary()[1] && _enemy->attributes.getDirection() == -1))
		{
			return false;
		}
		else
		{
			return true;
		}
	}


	bool EnemyIdleState::isNearPlayer()
	{
		float xDistance =
			abs(_enemy->attributes.getPosition().x - _data->player->getPlayerData()->attributes.getPosition().x);

		if (xDistance < ENEMY_ATTACK_RANGE)
			return true;
		else
			return false;
	}

	void EnemyIdleState::facePlayer()
	{
		if (_data->player->getPlayerData()->attributes.getPosition().x < _enemy->attributes.getPosition().x)
			_enemy->attributes.setDirection(1);
		else
			_enemy->attributes.setDirection(-1);
	}

}