#include "PlayerIdleState.h"
#include "PlayerRunState.h"
#include "PlayerAttackState.h"
#include "PlayerJumpState.h"
#include "PlayerHurtState.h"
#include "PlayerFallingState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	IdleState::IdleState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void IdleState::init()
	{
		// start animation
		initAnimation("idle");

		// set origin, scale & position
		initSprite();

		// initialise variables
		_player->attributes.setSpeed(STATIONARY);
		_collider.setLevel01();
	}


	void IdleState::handleInput()
	{
		// ATTACK
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			toAttackState();
		}
		// RUN left
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			toRunState(-1);
		}
		// RUN right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			toRunState(1);
		}		
		// JUMP
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			toJumpState();
		}
	}


	void IdleState::update(float dt)
	{
		//HURT
		if (_player->attributes.getTakingDmg())
		{
			toHurtState();
		}

		// FALLING
		if (_collider.falling(_player, sf::Vector2f(0.0f, GRAVITY * dt)))
		{
			toFallingState();
		}

		_player->animate.playLoop(3.5f);
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}


	void IdleState::draw()
	{
		_data->window.draw(_sprite);
	}


	void IdleState::resume()
	{
		initAnimation("idle");
		_sprite.setPosition(_player->attributes.getPosition());
	}


	// --- Private Functions ---

	void IdleState::initAnimation(std::string animation)
	{
		_player->animate.activateSheetFor(animation);
		_player->animate.newAnimation(animation);

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void IdleState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	void IdleState::toAttackState()
	{
		_player->machine.replaceState(stateRef(new AttackState(_data, _player)));
	}

	void IdleState::toRunState(int direction)
	{
		_player->attributes.setDirection(direction);
		_player->machine.replaceState(stateRef(new RunState(_data, _player)));
	}

	void IdleState::toJumpState()
	{
		_player->machine.addState(stateRef(new JumpState(_data, _player)));
	}

	void IdleState::toHurtState()
	{
		_player->attributes.setTakingDmg(false);
		_player->machine.addState(stateRef(new HurtState(_data, _player)));
	}

	void IdleState::toFallingState()
	{
		_player->machine.addState(stateRef(new FallingState(_data, _player)));
	}

}