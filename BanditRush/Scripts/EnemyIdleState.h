#pragma once
#include "Game.h"
#include "Enemy.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace srac
{
	class EnemyIdleState : public State
	{
	private:
		gameDataRef _data;
		enemyDataRef _enemy;

		environment::Collider _collider;

		sf::Sprite _sprite;

		// initialisations
		void initSprite();
		void initAnimation(std::string animation);

		// state changes
		void toAttackState();
		void toHurtState();
		void toRunState();

		bool isNearPlayer();
		bool isPlayerInRange(float range);
		void facePlayer();
		bool inBoundary();

		void beIdle();

	public:
		EnemyIdleState(gameDataRef data, enemyDataRef enemyData);

		void init();
		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();
		void resume();
	};
}