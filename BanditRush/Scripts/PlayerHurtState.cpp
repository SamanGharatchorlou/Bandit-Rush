#include "PlayerHurtState.h"
#include "PlayerDeadState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	HurtState::HurtState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void HurtState::init()
	{
		// start animation
		initAnimation("hurt");

		// set origin, scale & position
		initSprite();

		// initialise variables
		_player->attributes.setSpeed(STUMBLE_SPEED);
		_animationSpeed = 10.0f;
		_hasPlayed = false;
		_isDead = false;

		takeDamage();
	}


	void HurtState::update(float dt)
	{
		if (_player->animate.playSingle(_animationSpeed))
		{
			// DIE
			if (_isDead)
			{
				toDeadState();
			}
			// CONTINUE previous state
			else
			{
				_player->machine.removeState();
			}
		}

		if (_player->animate.partComplete(_animationSpeed, 30.0f))
		{
			hurt(dt);
			playSound("ouch", 150);
		}

		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void HurtState::draw()
	{
		_data->window.draw(_sprite);
	}


	// --- Private Functions ---

	void HurtState::initAnimation(std::string animation)
	{
		_player->animate.activateSheetFor(animation);
		_player->animate.newAnimation(animation);

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void HurtState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	void HurtState::playSound(std::string sound, int volume)
	{
		if (!_hasPlayed)
		{
			_sound.setBuffer(_data->asset.getSoundBuffer(sound));
			_sound.play();
			_sound.setVolume(volume);
			_hasPlayed = true;
		}
	}

	void HurtState::takeDamage()
	{
		_player->attributes.reduceHealth(1.0f);

		if (_player->attributes.getHealth() <= 0)
			_isDead = true;
	}

	void HurtState::hurt(float dt)
	{
		_player->attributes.move(_player->attributes.getDirection() * -1 * STUMBLE_SPEED * dt, 0);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	void HurtState::toDeadState()
	{
		_player->machine.replaceState(stateRef(new DeadState(_data, _player)));
	}

}