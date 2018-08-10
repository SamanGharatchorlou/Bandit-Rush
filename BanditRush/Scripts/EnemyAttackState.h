#pragma once
#include "Game.h"
#include "Enemy.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

namespace srac
{
	class EnemyAttackState : public State
	{
	private:
		gameDataRef _data;
		enemyDataRef _enemy;

		environment::Collider collider;

		sf::Sprite _sprite;
		sf::Sound _attackSound;

		float _animationSpeed;
		bool _hasPlayedSound;
		bool _hasAttacked;

		// initialisations
		void initSprite();
		void initAnimation(std::string animation);

		// updates
		void attack();
		void toIdle();
		void playSound();

		bool isPlayerInRange(float range);

	public:
		EnemyAttackState(gameDataRef data, enemyDataRef enemyData);

		void init();

		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();
	};
}