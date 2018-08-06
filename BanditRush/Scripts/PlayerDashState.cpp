#include "PlayerDashState.h"
#include "PlayerRunState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	DashState::DashState(gameDataRef data, playerDataRef playerData) : _data(data), _player(playerData) {	}

	void DashState::init()
	{
		// start animation
		initAnimation("dash");

		// set origin, scale & position
		initSprite();

		// play sounds
		initSound("woosh", 30);

		// initialise variables
		_dashTime = 0.08f;
		_lastImgIndex = 0;
		_player->attributes.dashCooldown();

		// MUST REMOVE THIS DEPENDANCY
		_collider.setLevel01();
	}


	void DashState::update(float dt)
	{
		dash(dt);
		imageEffect();

		// if animation finished
		if (_player->animate.playSingle(1.0f/_dashTime))
		{
			toRunState();
		}

		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void DashState::draw()
	{
		_data->window.draw(_sprite);
		drawImages();
	}


	// --- Private Functions ---

	void DashState::initAnimation(std::string animation)
	{
		_player->animate.activateSheetFor(animation);
		_player->animate.newAnimation(animation);

		_sprite.setTexture(_player->animate.getSpriteSheet());
		_sprite.setTextureRect(_player->animate.getActiveClip());
	}

	void DashState::initSprite()
	{
		_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height);
		_sprite.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);
		_sprite.setPosition(_player->attributes.getPosition());
	}

	void DashState::initSound(std::string sound, int volume)
	{
		_sound.setBuffer(_data->asset.getSoundBuffer(sound));
		_sound.play();
		_sound.setVolume(volume);
	}

	void DashState::dash(float dt)
	{
		_movement = sf::Vector2f(DASH_SPEED * _player->attributes.getDirection() * dt, 0);

		// if not bumping into a wall
		if (!_collider.colliding(_player, _movement))
		{
			_player->attributes.move(_movement);
			_sprite.setPosition(_player->attributes.getPosition());
		}
	}

	void DashState::imageEffect()
	{
		if (_imgTimer.getElapsedTime().asSeconds() > 0.02f)
		{
			spawnImage();
			_imgTimer.restart();
		}
	}

	void DashState::spawnImage()
	{
		sf::Sprite _mirrorImg;

		_mirrorImg.setTexture(_data->asset.getTexture("multi image"));

		_mirrorImg.setPosition(_player->attributes.getPosition());
		_mirrorImg.setOrigin(_mirrorImg.getGlobalBounds().width / 2, _mirrorImg.getGlobalBounds().height);
		_mirrorImg.setScale(PLAYER_SCALE * _player->attributes.getDirection(), PLAYER_SCALE);

		_multiImg.push_back(_mirrorImg);
	}

	void DashState::toRunState()
	{
		if(_player->machine.stateCount() > 1)
			_player->machine.removeState();
		else
			_player->machine.replaceState(stateRef(new RunState(_data, _player)));
	}

	void DashState::drawImages()
	{
		if (_multiImg.size() - _lastImgIndex > 4)
		{
			_lastImgIndex = _multiImg.size() - 4;
		}

		for (int i = _lastImgIndex; i < _multiImg.size(); i++)
		{
			_data->window.draw(_multiImg[i]);
		}
	}

}