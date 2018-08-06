#include "CharacterAttributes.h"
#include "Player.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	// get & set position
	void CharacterAttributes::setPosition(sf::Vector2f position) { _position = position; }
	void CharacterAttributes::setPosition(float xPosition, float yPosition)
	{
		_position.x = xPosition;
		_position.y = yPosition;
	}

	void CharacterAttributes::setPosition(float level)
	{
		switch (int(level))
		{
		case int(LEVEL_01) :
			// spawn left or right side
			if (rand() % 2 == 0)
				_position.x = -100.0f;
			else
				_position.x = 1100.0f;
			break;

		case int(LEVEL_02) :
			_position.x = -100.0f;
			break;

		case int(LEVEL_03) :
			_position.x = 1100.0f;
			break;

		default:
			break;
		}

		_position.y = level;
	}

	void CharacterAttributes::move(sf::Vector2f movement) { _position += movement; }
	void CharacterAttributes::move(float xMovement, float yMovement)
	{ 
		_position.x += xMovement;
		_position.y += yMovement;
	}

	sf::Vector2f CharacterAttributes::getPosition() { return _position; }

	// get & set direction
	void CharacterAttributes::setDirection(int direction) { _direction = direction; }
	void CharacterAttributes::flipDirection() { _direction *= -1; }
	int CharacterAttributes::getDirection() { return _direction; }

	// get & set size
	void CharacterAttributes::setSize(sf::Vector2f size) { _size = size; }
	sf::Vector2f CharacterAttributes::getSize() { return _size; }

	// get & set velocity
	sf::Vector2f CharacterAttributes::getVelocity() 
	{ 
		return sf::Vector2f(_velocity.x * _direction, - _velocity.y); 
	}

	void CharacterAttributes::setVelocity(sf::Vector2f velocity) 
	{ 
		_velocity.x = velocity.x;
		_velocity.y = velocity.y;
	}

	void CharacterAttributes::setVelocity(float xVelocity, float yVelocity) 
	{
		_velocity.x = xVelocity;
		_velocity.y = yVelocity;
	}

	void CharacterAttributes::setVelocityX(float xVelocity) { _velocity.x = xVelocity; }
	void CharacterAttributes::setVelocityY(float yVelocity) { _velocity.y = yVelocity; }

	void CharacterAttributes::changeVelocity(float xChange, float yChange)
	{
		_velocity.x += xChange;
		_velocity.y += yChange;
	}

	// get & set horizontal speed (enemy)
	void CharacterAttributes::initRandSpeed(float randFactor) { _randSpeedFactor = randFactor; }
	float CharacterAttributes::getRandSpeedFactor() { return _randSpeedFactor; }
	void CharacterAttributes::setRandSpeed(float speed) { _speed = speed * _randSpeedFactor; }

	void CharacterAttributes::setSpeed(float speed) { _speed = speed; }
	float CharacterAttributes::getSpeed() { return _speed; }

	// get & set health
	void CharacterAttributes::initRandHealth(float randFactor) { _randHpFactor = randFactor; }
	void CharacterAttributes::setRandHealth(float health) { _health = health * _randHpFactor; }

	float CharacterAttributes::getHealth() { return _health; }
	void CharacterAttributes::reduceHealth(float damage) { _health -= damage; }
	void CharacterAttributes::setHealth(float health) 
	{ 
		_health = health; 

		if (_health > 0)
			_isDead = false;
	}

	// get & set damage
	void CharacterAttributes::setDamage(float damage) { _damage = damage; }
	float CharacterAttributes::getDamage() { return _damage; }

	// is taking damage
	void CharacterAttributes::setTakingDmg(bool isTakingDamage) { _isTakingDamage = isTakingDamage; }
	bool CharacterAttributes::getTakingDmg() { return _isTakingDamage; }

	//die
	void CharacterAttributes::die() { _isDead = true; }
	void CharacterAttributes::alive() { _isDead = false; }
	bool CharacterAttributes::isDead() { return _isDead; }

	// attcking
	void CharacterAttributes::randAttackCooldown(float randFactor) 
	{ 
		_attackCD = ENEMY_ATTACK_CD * randFactor;
	}

	void CharacterAttributes::attackCooldown() { _attackDelayTimer.restart(); }
	bool CharacterAttributes::canAttack()
	{
		if (_attackDelayTimer.getElapsedTime().asSeconds() > _attackCD)
			return true;
		else
			return false;
	}

	// dashing
	void CharacterAttributes::dashCooldown() { _dashCDTimer.restart(); }
	bool CharacterAttributes::canDash()
	{
		if (_dashCDTimer.getElapsedTime().asSeconds() > DASH_CD)
			return true;
		else
			return false;
	}

	// kill count
	void CharacterAttributes::addKill() { _kills++; }
	int CharacterAttributes::getKills() { return _kills; }

	// enemy boundary
	void CharacterAttributes::setBoundary(float floorLevel) 
	{ 
		switch (int(floorLevel))
		{
		case int(LEVEL_01) :
			_boundary = { 0.0f, 2000.0f };
			break;
			
		case int(LEVEL_02) :
			_boundary = { -1000.0f, 400.0f };
			break;

		case int(LEVEL_03) :
			_boundary = { 640.0f, 2000.0f };
			break;

		default:
			_boundary = { 0.0f, 2000.0f };
			break;
		}
	}

	std::vector<float> CharacterAttributes::getBoundary() { return _boundary; }

	// ground level 
	float CharacterAttributes::getLevel(Player* player)
	{
		float playerY = player->getPlayerData()->attributes.getPosition().y;

		if (playerY < 250.0f)
		{
			return LEVEL_03;
		}
		else if (playerY < 525.0f)
		{
			return LEVEL_02;
		}
		else
		{
			return LEVEL_01;
		}
	}

	// can be used only from player object
	float CharacterAttributes::getLevel()
	{
		if (_position.y < 250.0f)
		{
			return LEVEL_03;
		}
		else if (_position.y  < 525.0f)
		{
			return LEVEL_02;
		}
		else
		{
			return LEVEL_01;
		}
	}

	int CharacterAttributes::getLevelIndex()
	{
		if (_position.y < 250.0f)
		{
			return 2;
		}
		else if (_position.y  < 525.0f)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	float CharacterAttributes::getLevel(int levelIndex)
	{
		if (levelIndex == 0)
		{
			return LEVEL_01;
		}
		else if (levelIndex == 1)
		{
			return LEVEL_02;
		}
		else
		{
			return LEVEL_03;
		}
	}
}