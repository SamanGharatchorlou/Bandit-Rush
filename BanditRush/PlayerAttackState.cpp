#include "PlayerAttackState.h"
#include "PlayerIdleState.h"
#include "PlayerHurtState.h"
#include "PlayerDashState.h"
#include "PlayerRunState.h"
#include "EnemyHurtState.h"
#include "DEFINITIONS.h"

#include <iostream>
#include <string>

namespace srac
{
	AttackState::AttackState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void AttackState::init()
	{
		// start animation
		initAnimations();

		// set origin, scale & position
		initSprite();

		// initialise variables
		_anim = 0;
		_keepAttacking = true;
		_hasAttacked = false;
		_firstHit = true;
	}


	void AttackState::handleInput()
	{
		_keepAttacking = (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? true : false);

		// DASH interrupt attack
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _player->attributes.canDash() && (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			toDashState();
		}

		// face LEFT
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			float direction = _player->attributes.getDirection();

			_player->attributes.setDirection(-1);

			if (_player->attributes.getDirection() != direction)
				toRunState();
		}
		// face RIGHT
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			float direction = _player->attributes.getDirection();

			_player->attributes.setDirection(+1);

			if (_player->attributes.getDirection() != direction)
				toRunState();
		}
	}

	void AttackState::update(float dt)
	{
		// HIT: interrupt attacking state
		if (_player->attributes.getTakingDmg())
		{
			toHurtState();
		}
		// ATTACK animation (loop)
		else if (_player->animate.playSingle(_animSpeeds[_anim]))
		{
			if (_keepAttacking)
				loopAnimations();
			else
				toIdleState();
		}

		// ATTACK enemies
		if (!_hasAttacked && _player->animate.partComplete(_animSpeeds[_anim], 30.0f))
		{
			attack();
			playSound(100);
		}

		moveDamageText(dt);

		_sprite.setTextureRect(_player->animate.getActiveClip());
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
	}


	void AttackState::draw()
	{
		_data->window.draw(_sprite);

		for (int i = 0; i < damageText.size(); i++)
		{
			_data->window.draw(damageText[i]);
		}
	}


	// --- Private Functions ---

	void AttackState::initAnimations()
	{
		// different attack animations and speeds
		_attackAnims.push_back("attack1");
		_attackAnims.push_back("attack2");
		_attackAnims.push_back("attack3");

		_animSpeeds.push_back(ATTACK1_SPEED);
		_animSpeeds.push_back(ATTACK2_SPEED);
		_animSpeeds.push_back(ATTACK3_SPEED);


		_player->animate.activateSheetFor("attack1");
		_player->animate.newAnimation("attack1");

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void AttackState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}


	// --- animation / sound ---

	void AttackState::loopAnimations()
	{
		_hasAttacked = false;
		_anim = (_anim < _attackAnims.size() - 1) ? _anim + 1 : 0;

		_player->animate.newAnimation(_attackAnims[_anim]);
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void AttackState::playSound(int volume)
	{
		// sound file indexes -> 0, 1, 2 = 1, 1, 2
		std::string soundName = "attack " + std::to_string(_anim / 2 + 1);

		_sound.setBuffer(_data->asset.getSoundBuffer(soundName));
		_sound.play();
		_sound.setVolume(volume);
	}


	// --- state changes ---

	void AttackState::toIdleState()
	{
		_player->machine.replaceState(stateRef(new IdleState(_data, _player)));
	}

	void AttackState::toDashState()
	{
		_player->machine.replaceState(stateRef(new DashState(_data, _player)));
	}

	void AttackState::toHurtState()
	{
		_player->machine.addState(stateRef(new HurtState(_data, _player)));
		_player->attributes.setTakingDmg(false);
	}

	void AttackState::toRunState()
	{
		_player->machine.replaceState(stateRef(new RunState(_data, _player)));
	}

	void AttackState::resume()
	{
		initAnimations();
		_sprite.setPosition(_player->attributes.getPosition());
	}


	// --- attack logic ---

	void AttackState::attack()
	{
		_hasAttacked = true;

		// check against all active enemies
		for (int i = 0; i < _data->enemyController.getEnemies().size(); i++)
		{
			damage(_data->enemyController.getEnemy(i)->getEnemyData());
		}
	}

	void AttackState::damage(enemyDataRef enemy)
	{
		//reduce enemy health if within range
		if (inRange(enemy, ATTACK_RANGE))
		{
			reduceEnemyHp(enemy);
			enemy->attributes.setTakingDmg(true);

			// spawn damage points
			spawnDamageText(enemy);
		}

		// force enemy death
		if(enemy->attributes.getHealth() <= 0.0f)
		{
			kill(enemy);
		}
	}

	bool AttackState::inRange(enemyDataRef enemy, float range)
	{
		// player attack box
		int playerDir = _player->attributes.getDirection() == -1 ? 1 : 0;

		sf::Vector2f playerPos = sf::Vector2f(
			_player->attributes.getPosition().x - (playerDir * range),
			_player->attributes.getPosition().y - range);

		sf::IntRect playerAttackBox = _collider.getBox(playerPos, range);

		sf::IntRect enemyBoxCollider = _collider.getBoxCollider(
			enemy->attributes.getPosition(), 
			enemy->attributes.getSize());

		if (playerAttackBox.intersects(enemyBoxCollider))
		{
			return true;
		}
		else
			return false;
	}

	void AttackState::reduceEnemyHp(enemyDataRef enemy)
	{
		enemy->attributes.reduceHealth(_player->attributes.getDamage());
		enemy->attributes.setTakingDmg(true);
	}

	void AttackState::kill(enemyDataRef enemy)
	{
		if (!enemy->attributes.isDead())
		{
			enemy->attributes.die();
			enemy->machine.replaceState(stateRef(new EnemyHurtState(_data, enemy)));
		}
	}


	// --- damage text ---

	void AttackState::spawnDamageText(enemyDataRef enemy)
	{
		sf::Text damagePoint;
		damagePoint.setFont(_data->asset.getFont("game font"));
		damagePoint.setString(std::to_string(int(_player->attributes.getDamage())));
		damagePoint.setCharacterSize(7);
		damagePoint.setFillColor(sf::Color::Yellow);


		int direction = _player->attributes.getDirection();

		float xOffset = direction == 1 ? 0.25f : -1.25f;

		damagePoint.setPosition(
			enemy->attributes.getPosition().x + xOffset * ENEMY_WIDTH,
			enemy->attributes.getPosition().y - enemy->attributes.getSize().y);

		damageText.push_back(damagePoint);

		textDirection.push_back(sf::Vector2f(direction * (rand() % 101), (rand() % 201) - 100) / 100.0f);
	}

	void AttackState::moveDamageText(float dt)
	{
		for (int i = 0; i < damageText.size(); i++)
		{
			// movement
			damageText[i].move(textDirection[i].x * DMG_TXT_MOVE_SPEED * dt,
				textDirection[i].y * DMG_TXT_MOVE_SPEED * dt);

			// fade
			if(damageText[i].getFillColor().a > DMG_TXT_FADE_SPEED)
				damageText[i].setFillColor(sf::Color(255, 255, 0, damageText[i].getFillColor().a - DMG_TXT_FADE_SPEED));
		}
	}
}
