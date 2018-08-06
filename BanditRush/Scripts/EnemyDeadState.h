#pragma once
#include "Game.h"
#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace srac
{
	class EnemyDeadState : public State
	{
	private:
		gameDataRef _data;
		enemyDataRef _enemy;

		sf::Sprite _sprite;

		void initSprite();
		void initAnimation(std::string animation);

		void recycleDead();

	public:
		EnemyDeadState(gameDataRef data, enemyDataRef enemyData);

		void init();

		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();
	};
}