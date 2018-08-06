#pragma once
#include "Game.h"
#include "StateMachine.h"
#include "CharacterAttributes.h"
#include "EnemyAnimator.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace srac
{
	struct EnemyData
	{
		StateMachine machine;
		CharacterAttributes attributes;
		EnemyAnimator animator;
	};

	typedef std::shared_ptr<EnemyData> enemyDataRef;

	class Enemy
	{
	private:
		gameDataRef _data;
		enemyDataRef _enemy = std::make_shared<EnemyData>();

		float randSpeed;
		float randAttackCd;
		float randHealth;

	public:
		Enemy(gameDataRef data);

		void init(Player* player);

		void processStateChanges();
		void handleInput();
		void update(float dt);
		void draw();

		enemyDataRef getEnemyData();
	};
}