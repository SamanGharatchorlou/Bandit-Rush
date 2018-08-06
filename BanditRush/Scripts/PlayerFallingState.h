#pragma once
#include "Game.h"
#include "Player.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>

namespace srac
{
	class FallingState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		environment::Collider _collider;

		sf::Vector2f _movement;

		sf::Sprite _sprite;

		bool _canFlip;

		float _maxSpeed;

		// initialisations
		void initAnimation(std::string animation);
		void initSprite();

		// state changes
		void toFlipState();

		// updates
		void fall(float xMovement, float yMovement);
		void applyGravity();

	public:
		FallingState(gameDataRef data, playerDataRef playerData);

		void init();

		void preProcess() { }
		void handleInput();
		void update(float dt);
		void draw();
	};
}