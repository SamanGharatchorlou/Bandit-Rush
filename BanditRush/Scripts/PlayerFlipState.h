#pragma once
#include "Game.h"
#include "Player.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace srac
{
	class FlipState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		environment::Collider _collider;

		sf::Vector2f _movement;

		sf::Sprite _sprite;

		sf::SoundBuffer _buffer;
		sf::Sound _sound;

		// initialisations
		void initAnimation(std::string animation);
		void initSprite();
		void initSound(std::string sound, int volume);

		// state changes
		void toIdleState();
		void toFallingState();

		// updates
		void flip();

	public:
		FlipState(gameDataRef data, playerDataRef playerData);

		void init();

		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();
	};
}