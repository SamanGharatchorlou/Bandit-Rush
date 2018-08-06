#pragma once
#include "Game.h"
#include "Enemy.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace srac
{
	class EnemyRunState : public State
	{
	private:
		gameDataRef _data;
		enemyDataRef _enemy;

		environment::Collider _collider;

		sf::Sprite _sprite;

		float _animationSpeed;

		void initSprite();
		void initAnimation(std::string animation);
		bool isPlayerInRange(float range);

		bool isNearPlayer();
		void facePlayer();
		void runForwards(float dt);
		bool inBoundary();

		void toHurtState();
		void toAttackState();
		void toIdleState();

	public:
		EnemyRunState(gameDataRef data, enemyDataRef enemyData);

		void init();
		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();
		void resume();


	};
}