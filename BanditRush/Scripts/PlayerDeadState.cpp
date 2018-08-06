#include "PlayerDeadState.h"
#include "GameOverState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	DeadState::DeadState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void DeadState::init()
	{
		// start animation
		initAnimation("die");

		// set origin, scale & position
		initSprite();

		// initialise variables
		_animationTime = 4.0f;
	}


	void DeadState::update(float dt)
	{
		if (_player->animate.playSingle(_animationTime))
		{
			_player->attributes.die();
		}

		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void DeadState::draw()
	{
		_data->window.draw(_sprite);
	}


	// --- Private Functions ---

	void DeadState::initAnimation(std::string animation)
	{
		_player->animate.activateSheetFor(animation);
		_player->animate.newAnimation(animation);

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void DeadState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	//void DeadState::playSound(std::string sound, int volume)
	//{
	//	if (!_hasPlayed)
	//	{
	//		_sound.setBuffer(_data->asset.getSoundBuffer(sound));
	//		_sound.play();
	//		_sound.setVolume(volume);
	//		_hasPlayed = true;
	//	}
	//}

}