#pragma once
#include "Game.h"
#include "Player.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>

namespace srac
{
	class RunState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		environment::Collider _collider;

		sf::Sprite _sprite;
		bool _hasDirection;
		bool _canAttack;

		// initialisations
		void initAnimation(std::string animation);
		void initSprite();

		// state changes
		void toIdleState();
		void toJumpState();
		void toHurtState();
		void toFallingState();
		void toDashState();

		// updates
		void run(sf::Vector2f movement);

	public:
		RunState(gameDataRef data, playerDataRef playerData);

		void init();
		void preProcess() { }
		void handleInput();
		void update(float dt);
		void draw();
		void resume();
	};
}