#pragma once
#include "Game.h"
#include "Enemy.h"

#include <SFML/Graphics.hpp>

namespace srac
{
	class EnemyHurtState : public State
	{
	private:
		gameDataRef _data;
		enemyDataRef _enemy;

		sf::Sprite _sprite;

		void initSprite();
		void initAnimation(std::string animation);

		void toHurtState();
		void toDeadState();

		void facePlayer();

	public:
		EnemyHurtState(gameDataRef data, enemyDataRef enemyData);

		void init();

		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();

	};
}