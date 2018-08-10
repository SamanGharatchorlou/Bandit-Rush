#pragma once
#include "Game.h"
#include "StateMachine.h"
#include "CharacterAttributes.h"
#include "EnemyAnimator.h"

#include <memory>
#include <SFML/Graphics.hpp>

namespace srac
{
	struct KnightData
	{
		StateMachine machine;
		CharacterAttributes attributes;
		EnemyAnimator animate;
	};

	typedef std::shared_ptr<KnightData> knightDataRef;

	class Knight
	{
	private:
		gameDataRef _data;
		knightDataRef _knight = std::make_shared<KnightData>();

	public:
		Knight(gameDataRef data);

		void processStateChanges();
		void handleInput();
		void update(float dt);
		void draw();

		//knightDataRef getPlayerData();
	};
}