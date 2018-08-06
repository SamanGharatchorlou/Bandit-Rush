#include "EnemyRunState.h"
#include "EnemyHurtState.h"
#include "EnemyIdleState.h"
#include "EnemyAttackState.h"
#include "Player.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	EnemyRunState::EnemyRunState(gameDataRef data, enemyDataRef enemyData) : _data(data), _enemy(enemyData) {	}

	void EnemyRunState::init()
	{
		// start run animation
		initAnimation("run");

		// set origin, scale & position
		initSprite();

		// initialise variables
		_enemy->attributes.setRandSpeed(ENEMY_RUN_SPEED);
		_enemy->attributes.setTakingDmg(false);
		_animationSpeed = 6.0f * _enemy->attributes.getRandSpeedFactor();
	}


	void EnemyRunState::update(float dt)
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
		// IDLE
		else if (isNearPlayer() || !inBoundary())
		{
			toIdleState();
		}

		// RUN
		if(!isNearPlayer())
		{
			facePlayer();
			runForwards(dt);
		}

		_sprite.setScale(ENEMY_SCALE * _enemy->attributes.getDirection(), ENEMY_SCALE);

		_enemy->animator.playLoop(_animationSpeed);
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyRunState::draw()
	{
		_data->window.draw(_sprite);
	}

	void EnemyRunState::resume()
	{
		_enemy->animator.newAnimation("run");
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}


	// --- Private Functions ---

	void EnemyRunState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width * ENEMY_CENTER, _sprite.getGlobalBounds().height);
		_sprite.setScale(ENEMY_SCALE * _enemy->attributes.getDirection(), ENEMY_SCALE);
		_sprite.setPosition(_enemy->attributes.getPosition());
	}

	void EnemyRunState::initAnimation(std::string animation)
	{
		_enemy->animator.newAnimation(animation);
		_sprite.setTexture(_enemy->animator.getSpriteSheet());
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyRunState::runForwards(float dt)
	{
		_enemy->attributes.move(-_enemy->attributes.getDirection() * _enemy->attributes.getSpeed() * dt, 0);
		_sprite.setPosition(_enemy->attributes.getPosition());
	}

	bool EnemyRunState::isNearPlayer()
	{
		float xDistance =
			abs(_enemy->attributes.getPosition().x - _data->player->getPlayerData()->attributes.getPosition().x);

		if (xDistance < ENEMY_ATTACK_RANGE)
			return true;
		else
			return false;
	}

	bool EnemyRunState::isPlayerInRange(float range)
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
			return true;
		else
			return false;
	}

	bool EnemyRunState::inBoundary()
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

	void EnemyRunState::facePlayer()
	{
		if(_data->player->getPlayerData()->attributes.getPosition().x < _enemy->attributes.getPosition().x)
			_enemy->attributes.setDirection(1);
		else
			_enemy->attributes.setDirection(-1);
	}

	void EnemyRunState::toAttackState()
	{
		_enemy->machine.replaceState(stateRef(new EnemyAttackState(_data, _enemy)));
	}

	void EnemyRunState::toHurtState()
	{
		_enemy->machine.addState(stateRef(new EnemyHurtState(_data, _enemy)));
	}

	void EnemyRunState::toIdleState()
	{
		_enemy->machine.replaceState(stateRef(new EnemyIdleState(_data, _enemy)));
	}

}