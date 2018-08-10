#pragma once
#pragma once
#include "Game.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

namespace srac
{
	class DeadState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		sf::Sprite _sprite;
		sf::Sound _sound;

		float _animationTime;

		// initialisations
		void initAnimation(std::string animation);
		void initSprite();
		void playSound(std::string sound, int volume);

	public:
		DeadState(gameDataRef data, playerDataRef playerData);

		void init();

		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();
	};
}