#pragma once
#include "Game.h"
#include "Player.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>

namespace srac
{
	class IdleState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		environment::Collider _collider;

		sf::Sprite _sprite;

		// initialisations
		void initAnimation(std::string animation);
		void initSprite();

		// state changes
		void toAttackState();
		void toRunState(int direction);
		void toJumpState();
		void toHurtState();
		void toFallingState();

	public:
		IdleState(gameDataRef data, playerDataRef playerData);

		void init();

		void preProcess() { }
		void handleInput();
		void update(float dt);
		void draw();

		void resume();
	};
}