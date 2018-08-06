#pragma once
#include "Game.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace srac
{
	class HurtState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		sf::Sprite _sprite;
		sf::Sound _sound;

		float _animationSpeed;
		bool _isDead;
		bool _hasPlayed;

		// initialisations
		void initAnimation(std::string animation);
		void initSprite();
		void playSound(std::string sound, int volume);

		// state changes
		void toDeadState();

		void takeDamage();
		void hurt(float dt);

	public:
		HurtState(gameDataRef data, playerDataRef playerData);

		void init();

		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();
	};
}