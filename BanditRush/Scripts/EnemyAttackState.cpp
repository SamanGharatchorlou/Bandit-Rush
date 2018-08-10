#include "EnemyAttackState.h"
#include "EnemyIdleState.h"
#include "Player.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	EnemyAttackState::EnemyAttackState(gameDataRef data, enemyDataRef enemyData) : _data(data), _enemy(enemyData) {	}

	void EnemyAttackState::init()
	{
		initAnimation("attack");

		// set origin, scale & position
		initSprite();

		// attack sound
		_attackSound.setBuffer(_data->asset.getSoundBuffer("enemy attack"));

		// initialise variables
		_enemy->attributes.randAttackCooldown((((rand() % 100) - 50) / 100.0f) + 1.0f);
		_enemy->attributes.setTakingDmg(false);
		_animationSpeed = 3.5f;
		_hasPlayedSound = false;
		_hasAttacked = false;

		_enemy->animator.resetClock();
	}

	void EnemyAttackState::update(float dt)
	{
		playSound();

		// ATTACK player
		if(!_hasAttacked)
			attack();

		// IDLE (end attack)
		if (_enemy->animator.playSingle(_animationSpeed))
		{
			toIdle();
		}    
  
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyAttackState::draw()
	{
		_data->window.draw(_sprite);
	}


	// --- Private Functions ---

	void EnemyAttackState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width * ENEMY_CENTER, _sprite.getGlobalBounds().height);
		_sprite.setScale(ENEMY_SCALE * _enemy->attributes.getDirection(), ENEMY_SCALE);
		_sprite.setPosition(_enemy->attributes.getPosition());
	}

	void EnemyAttackState::initAnimation(std::string animation)
	{
		_enemy->animator.newAnimation(animation);
		_sprite.setTexture(_enemy->animator.getSpriteSheet());
		_sprite.setTextureRect(_enemy->animator.getActiveClip());
	}

	void EnemyAttackState::attack()
	{
		if (_enemy->animator.partComplete(_animationSpeed, 30.0f))
		{
			if (isPlayerInRange(ENEMY_HIT_RANGE))
			{
				_data->player->getPlayerData()->attributes.setTakingDmg(true);

				// force player to face enemy if hit
				int direction = _enemy->attributes.getDirection() == 1 ? 1 : - 1;
				_data->player->getPlayerData()->attributes.setDirection(direction);
			}

			// restart attack cooldown timer
			_enemy->attributes.attackCooldown();
			_hasAttacked = true;
		}
	}

	bool EnemyAttackState::isPlayerInRange(float range)
	{
		sf::Vector2f playerPos = _data->player->getPlayerData()->attributes.getPosition();
		sf::Vector2f playerSize = _data->player->getPlayerData()->attributes.getSize();

		// adjust enemy attack collision box depending on direction
		int enemyDir = _enemy->attributes.getDirection() == 1 ? 1 : 0;

		sf::Vector2f enemyPos = sf::Vector2f(
			_enemy->attributes.getPosition().x - (enemyDir * range),
			_enemy->attributes.getPosition().y - range);

		sf::IntRect enemyAttackBox = collider.getBox(enemyPos, range);
		sf::IntRect playerBoxCollider = collider.getBoxCollider(playerPos, playerSize);

		if (enemyAttackBox.intersects(playerBoxCollider))
		{
			return true;
		}
		else
			return false;
	}

	void EnemyAttackState::toIdle()
	{
		// prevent delayed responses
		_data->player->getPlayerData()->attributes.setTakingDmg(false);

		_enemy->machine.replaceState(stateRef(new EnemyIdleState(_data, _enemy)));
	}

	void EnemyAttackState::playSound()
	{
		if (!_hasPlayedSound && _enemy->animator.partComplete(_animationSpeed, 25.0))
		{
			_attackSound.play();
			_hasPlayedSound = true;
		}
	}
}