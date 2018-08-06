#include "PlayerJumpState.h"
#include "PlayerFallingState.h"
#include "PlayerFlipState.h"
#include "PlayerDashState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	JumpState::JumpState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void JumpState::init()
	{
		// start animation
		initAnimation("jump");

		// set origin, scale & position
		initSprite();

		// play sound
		initSound("jump");

		// initialise variables
		_canFlip = false;

		_player->attributes.setVelocity(_player->attributes.getSpeed(), 0);

		// REMOVE DEPENDENCY
		_collider.setLevel01();

		// JUMP
		jump();
	}

	void JumpState::handleInput()
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			_canFlip = true;
		}

		if (_canFlip && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			toFlipState();
		}

		// get direction
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// LEFT
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				_player->attributes.setDirection(-1);
			// RIGHT
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_player->attributes.setDirection(+1);

			_player->attributes.setVelocityX(FALL_DRIFT);
		}
		else
		{
			_player->attributes.setVelocityX(STATIONARY);
		}
	}

	void JumpState::update(float dt)
	{	
		applyGravity();

		sf::Vector2f movement = _player->attributes.getVelocity() * dt;

		if (!_collider.colliding(_player, movement))
		{
			_player->attributes.move(movement);
		}

		// begin FALLING at peak
		if (_player->attributes.getVelocity().y > 0)
		{
			toFallingState();
		}

		_player->animate.playLoop(5.0f);

		_sprite.setPosition(_player->attributes.getPosition());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void JumpState::draw()
	{
		_data->window.draw(_sprite);
	}


	// --- Private Functions ---

	void JumpState::initAnimation(std::string animation)
	{
		_player->animate.activateSheetFor(animation);
		_player->animate.newAnimation(animation);

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void JumpState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	void JumpState::initSound(std::string sound)
	{
		_sound.setBuffer(_data->asset.getSoundBuffer("jump"));
		_sound.setVolume(80);
		_sound.play();
	}

	void JumpState::toFlipState()
	{
		_player->machine.replaceState(stateRef(new FlipState(_data, _player)));
	}

	void JumpState::toFallingState()
	{
		_player->machine.replaceState(stateRef(new FallingState(_data, _player)));
	}

	void JumpState::jump()
	{
		_player->attributes.setVelocityY(JUMP_FORCE);
	}

	void JumpState::applyGravity()
	{
		_player->attributes.changeVelocity(0, -GRAVITY);
	}
}