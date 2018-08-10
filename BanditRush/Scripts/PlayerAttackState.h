#pragma once
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

namespace srac
{
	class AttackState : public State
	{
	private:
		gameDataRef _data;
		playerDataRef _player;

		environment::Collider _collider;

		sf::Sprite _sprite;
		sf::Sound _sound;
		int _soundIndex;
		bool _firstHit;

		std::vector<std::string> _attackAnims;
		std::vector<float> _animSpeeds;

		std::vector<sf::Text> damageText;
		std::vector<sf::Vector2f> textDirection;

		// animations
		int _anim;
		bool _hasAttacked;
		bool _keepAttacking;

		// attack enemy
		void damage(enemyDataRef enemy);
		bool inRange(enemyDataRef enemy, float range);
		void reduceEnemyHp(enemyDataRef enemy);

		// damage text
		void spawnDamageText(enemyDataRef enemy);
		void moveDamageText(float dt);

		// ----------------- NEW

		// initialisations
		void initAnimations();
		void initSprite();

		// state changes
		void toIdleState();
		void toHurtState();
		void toDashState();
		void toRunState();
		void kill(enemyDataRef enemy);

		void attack();

		void loopAnimations();
		void playSound(int volume);

	public:
		AttackState(gameDataRef data, playerDataRef playerData);

		void init();

		void preProcess() { }
		void handleInput();
		void update(float dt);
		void draw();

		void resume();
	};
}