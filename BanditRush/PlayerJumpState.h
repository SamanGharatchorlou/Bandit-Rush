#pragma once
#include "Game.h"
#include "Player.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace srac
{
	class JumpState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		environment::Collider _collider;

		sf::Sprite _sprite;

		sf::SoundBuffer _buffer;
		sf::Sound _sound;

		bool _canFlip;

		// initialisations
		void initAnimation(std::string animation);
		void initSprite();
		void initSound(std::string sound);

		// state changes
		void toFlipState();
		void toFallingState();

		// updates
		void jump();
		void applyGravity();


	public:
		JumpState(gameDataRef data, playerDataRef playerData);

		void init();

		void preProcess() { }
		void handleInput();
		void update(float dt);
		void draw();
	};
}