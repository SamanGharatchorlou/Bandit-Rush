#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace srac
{
	class Player;

	class CharacterAttributes
	{
	private:
		sf::Vector2f _position;
		int _direction;

		sf::Vector2f _size;

		sf::Vector2f _velocity;

		float _randSpeedFactor;
		float _speed;

		float _randHpFactor;
		float _health;

		float _damage;
		bool _isTakingDamage;
		bool _isDead;

		int _kills;

		bool _attack;
		float _attackCD;
		sf::Clock _attackDelayTimer;

		std::vector<float> _boundary;

		sf::Clock _dashCDTimer;

	public:
		// position
		void setPosition(sf::Vector2f position);
		void setPosition(float xPosition,  float yPosition);
		void setPosition(float level);

		void move(sf::Vector2f movement);
		void move(float x, float y);

		sf::Vector2f getPosition();

		// direction
		void setDirection(int direction);
		void flipDirection();
		int getDirection();

		// size of actual character, not sprite (for collisions)
		void setSize(sf::Vector2f size);
		sf::Vector2f getSize();

		// speed / velocity
		sf::Vector2f getVelocity();
		void setVelocity(sf::Vector2f velocity);
		void setVelocity(float xVelocity, float yVelocity);
		void setVelocityX(float xVelocity);
		void setVelocityY(float yVelocity);
		void changeVelocity(float xChange, float yChange);

		void initRandSpeed(float randFactor);
		float getRandSpeedFactor();
		void setRandSpeed(float speed);

		void setSpeed(float speed);
		float getSpeed();

		// health
		void initRandHealth(float randFactor);
		void setRandHealth(float health);

		void setHealth(float health);
		float getHealth();
		
		void reduceHealth(float damage);

		// damage
		void setDamage(float damage);
		float getDamage();

		// is taking damage
		void setTakingDmg(bool isTakingDamage);
		bool getTakingDmg();

		// is dead
		void die();
		void alive();
		bool isDead();

		// attack CD
		void randAttackCooldown(float randFactor);
		void attackCooldown();
		bool canAttack();

		// dash CD
		void dashCooldown();
		bool canDash();

		// kills
		void addKill();
		int getKills();

		// enemy boundary
		void setBoundary(float floorLevel);
		std::vector<float> getBoundary();

		// ground level
		float getLevel(Player* player);
		float getLevel();
		float getLevel(int levelIndex);
		int getLevelIndex();
	};
}