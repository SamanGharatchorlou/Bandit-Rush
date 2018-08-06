#pragma once
#pragma once
#include "Game.h"
#include "Player.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

namespace srac
{
	class DashState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		environment::Collider _collider;

		sf::Vector2f _movement;

		sf::Sprite _sprite;
		std::vector<sf::Sprite> _multiImg;

		sf::Sound _sound;

		float _dashTime;
		sf::Clock _imgTimer;
		int _lastImgIndex;

		// initialisations
		void initAnimation(std::string animation);
		void initSprite();
		void initSound(std::string sound, int volume);

		// state changes
		void toRunState();

		void dash(float dt);
		void imageEffect();
		void spawnImage();
		void drawImages();

	public:
		DashState(gameDataRef data, playerDataRef playerData);

		void init();
		void preProcess() { }
		void handleInput() { }
		void update(float dt);
		void draw();

	};
}