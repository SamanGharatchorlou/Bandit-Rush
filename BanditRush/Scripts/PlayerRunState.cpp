#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerDashState.h"
#include "PlayerFallingState.h"
#include "PlayerHurtState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	RunState::RunState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void RunState::init()
	{
		// start animation
		initAnimation("run");

		// set origin, scale & position
		initSprite();

		// initialise variables
		_player->attributes.setSpeed(RUN_SPEED);
		_hasDirection = false;
		_canAttack = false;
		_collider.setLevel01();
	}


	void RunState::handleInput()
	{
		if (!_canAttack && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_canAttack = true;

		// LEFT or RIGHT arrow is pressed
		_hasDirection = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? true : false;

		//DASH
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _player->attributes.canDash())
		{
			toDashState();
		}
		// JUMP
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _hasDirection)
		{
			toJumpState();
		}
		// ATTACK: idle -> attack
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _canAttack)
		{
			toIdleState();
		}

		// get direction
		if (_hasDirection)
		{
			// LEFT
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				_player->attributes.setDirection(-1);
			// RIGHT
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_player->attributes.setDirection(+1);
		}
		// IDLE (no direction)
		else
		{
			toIdleState();
		}
	}


	void RunState::update(float dt)
	{
		sf::Vector2f movement = sf::Vector2f(_player->attributes.getDirection() * RUN_SPEED * dt, 0);

		// FALLING
		if (_collider.falling(_player, sf::Vector2f(0.0f, GRAVITY * dt)))
		{
			toFallingState();
		}
		// not bumping into a SIDE WALL
		else if (!_collider.colliding(_player, movement))
		{
			run(movement);
		}

		// HIT
		if (_player->attributes.getTakingDmg())
		{
			toHurtState();
		}

		_player->animate.playLoop(5.0f);
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void RunState::draw()
	{
		_data->window.draw(_sprite);
	}

	void RunState::resume()
	{
		initAnimation("run");
		_sprite.setPosition(_player->attributes.getPosition());
	}



	// --- Private Functions ---

	void RunState::initAnimation(std::string animation)
	{
		_player->animate.activateSheetFor(animation);
		_player->animate.newAnimation(animation);

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void RunState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	void RunState::run(sf::Vector2f movement)
	{
		_player->attributes.move(movement);
		_sprite.setPosition(_player->attributes.getPosition());

		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
	}

	void RunState::toDashState()
	{
		_player->machine.addState(stateRef(new DashState(_data, _player)));
	}

	void RunState::toJumpState()
	{
		_player->machine.addState(stateRef(new JumpState(_data, _player)));
	}

	void RunState::toIdleState()
	{
		_player->machine.replaceState(stateRef(new IdleState(_data, _player)));
	}

	void RunState::toHurtState()
	{
		_player->attributes.setTakingDmg(false);
		_player->machine.addState(stateRef(new HurtState(_data, _player)));
	}

	void RunState::toFallingState()
	{
		_player->machine.addState(stateRef(new FallingState(_data, _player)));
	}
}