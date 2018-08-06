#include "PlayerFallingState.h"
#include "PlayerFlipState.h"
#include "PlayerDashState.h"
#include "PlayerIdleState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	FallingState::FallingState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void FallingState::init()
	{
		// start animation
		initAnimation("fall");

		// set origin, scale & position
		initSprite();

		// initialise variables
		_canFlip = false;
		_player->attributes.setVelocity(_player->attributes.getSpeed(), 0);
		_maxSpeed = 350.0f;

		// REMOVE DEPENDENCY
		_collider.setLevel01();
	}


	void FallingState::handleInput()
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

	void FallingState::toFlipState()
	{
		_player->machine.replaceState(stateRef(new FlipState(_data, _player)));
	}

	void FallingState::update(float dt)
	{
		applyGravity();

		_movement = _player->attributes.getVelocity() * dt;


		// GROUNDED
		if (_collider.grounded(_player, _movement))
		{
			_player->machine.removeState();
		}
		// SIDE WALL (no x movement)
		else if(_collider.colliding(_player, _movement))
		{
			// does this need to consider which side the wall is on?????
			fall(0, _movement.y);
		}
		else
		{
			fall(_movement.x, _movement.y);
		}

		_player->animate.playLoop(8.0f);

		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void FallingState::draw()
	{
		_data->window.draw(_sprite);
	}


	// --- Private Functions ---

	void FallingState::initAnimation(std::string animation)
	{
		_player->animate.activateSheetFor(animation);
		_player->animate.newAnimation(animation);

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void FallingState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	void FallingState::fall(float xMovement, float yMovement)
	{
		_player->attributes.move(xMovement, yMovement);
		_sprite.setPosition(_player->attributes.getPosition());
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
	}

	void FallingState::applyGravity()
	{
		if (_player->attributes.getVelocity().y < _maxSpeed)
			_player->attributes.changeVelocity(0, -GRAVITY * 1.3f);
	}

}