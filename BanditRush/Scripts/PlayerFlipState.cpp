#include "PlayerFlipState.h"
#include "PlayerFallingState.h"
#include "PlayerIdleState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	FlipState::FlipState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void FlipState::init()
	{
		// start animation
		initAnimation("flip");

		// set origin, scale & position
		initSprite();

		// play sound
		initSound("flip", 100);

		// MUST REMOVE THIS DEPENDANCY
		_collider.setLevel01();
	}


	void FlipState::update(float dt)
	{
		if (_player->attributes.getSpeed() == STATIONARY)
			_movement = sf::Vector2f(0.0f, -GRAVITY / 3.0f * dt);
		else
			_movement = sf::Vector2f(_player->attributes.getDirection() * FLIP_SPEED * dt, -GRAVITY / 3.0f * dt);

		// GROUNDED
		if (_collider.grounded(_player, _movement))
		{
			toIdleState();
		}
		// SIDE WALL
		else if(!_collider.colliding(_player, _movement))
		{
			flip();
		}

		// if animation finished
		if (_player->animate.playSingle(15.0f))
		{
			toFallingState();
		}

		_sprite.setTextureRect(_player->animate.getActiveClip());
	}


	void FlipState::draw()
	{
		_data->window.draw(_sprite);
	}


	// --- Private Functions ---

	void FlipState::initAnimation(std::string animation)
	{
		_player->animate.activateSheetFor(animation);
		_player->animate.newAnimation(animation);

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void FlipState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	void FlipState::initSound(std::string sound, int volume)
	{
		_sound.setBuffer(_data->asset.getSoundBuffer("flip"));
		_sound.play();        
		_sound.setVolume(volume);	
	}

	void FlipState::toFallingState()
	{
		_player->machine.replaceState(stateRef(new FallingState(_data, _player)));
	}

	void FlipState::toIdleState()
	{
		_player->machine.replaceState(stateRef(new IdleState(_data, _player)));
	}

	void FlipState::flip()
	{
		_player->attributes.move(_movement);
		_sprite.setPosition(_player->attributes.getPosition());
	}

}