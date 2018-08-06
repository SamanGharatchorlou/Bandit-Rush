#pragma once
#include "Game.h"
#include "StateMachine.h"
#include "CharacterAttributes.h"
#include "PlayerAnimator.h"

#include <memory>

#include <SFML/Graphics.hpp>

namespace srac
{
	struct PlayerData
	{
		StateMachine machine;
		CharacterAttributes attributes;
		PlayerAnimator animate;
	};

	typedef std::shared_ptr<PlayerData> playerDataRef;

	class Player
	{
	private:
		gameDataRef _data;
		playerDataRef _player = std::make_shared<PlayerData>();

	public:
		Player(gameDataRef data);

		void processStateChanges();
		void handleInput();
		void update(float dt);
		void draw();

		playerDataRef getPlayerData();
	};
}