#include "Player.h"
#include "PlayerIdleState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	Player::Player(gameDataRef data) : _data(data)
	{
		_player->attributes.setPosition(35, 90);
		_player->attributes.setDirection(1);

		_player->attributes.setSize(sf::Vector2f(CHARACTER_WIDTH, CHARACTER_HEIGHT));

		_player->machine.addState(stateRef(new IdleState(_data, _player)));

		_player->attributes.setDamage(ATTACK_DAMAGE);
		_player->attributes.setHealth(4.0f);
	}

	void Player::processStateChanges()
	{
		_player->machine.processStateChanges();
	}

	void Player::handleInput()
	{
		_player->machine.getActiveState()->handleInput();
	}

	void Player::update(float dt)
	{
		_player->machine.getActiveState()->update(dt);
	}

	void Player::draw()
	{
		_player->machine.getActiveState()->draw();
	}

	playerDataRef Player::getPlayerData()
	{
		return _player;
	}
}