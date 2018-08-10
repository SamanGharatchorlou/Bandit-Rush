#include "MainMenuState.h"
#include "GameState.h"

#include <iostream>

namespace srac
{
	MainMenuState::MainMenuState(gameDataRef data) : _data(data) {  }

	void MainMenuState::init()
	{
		_backgroundLayers = _data->asset.getBackgroundLayers();

		//title
		initTitle();

		// sound
		initSound();

		// Instructions
		initInstructions();
	}

	void MainMenuState::handleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}

			// sound
			if (_data->input.isSpriteClicked(_music, sf::Mouse::Left, _data->window))
			{
				// if on change to off
				if (_music.getTextureRect().left == 0)
				{
					_music.setTextureRect(sf::IntRect(75, 0, 65, 60));
					_gameMusic.setVolume(0);
				}
				// if off change to on
				else
				{
					_music.setTextureRect(sf::IntRect(0, 0, 65, 60));
					_gameMusic.setVolume(100);
				}
			}

			// A
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				greyText(_textA);
				greyKey(_keyA);
			}
			// D
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				greyText(_textD);
				greyKey(_keyD);
			}
			// SPACE
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				greyText(_textSpace);
				_keySpace.setTextureRect(greySpace);
			}

			// UP
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				greyKey(_arrowU);
			}

			// DOWN
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				greyKey(_arrowD);
			}

			// LEFT
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				greyKey(_arrowL);
			}

			// RIGHT
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				greyKey(_arrowR);
			}

		}
	}

	void MainMenuState::update(float dt)
	{
		if (_keyA.getTextureRect() == greyButton && _keyD.getTextureRect() == greyButton && _keySpace.getTextureRect() == greySpace &&
			_arrowU.getTextureRect() == greyButton && _arrowD.getTextureRect() == greyButton && _arrowL.getTextureRect() == greyButton && _arrowR.getTextureRect() == greyButton)
		{
			_data->machine.replaceState(stateRef(new GameState(_data)));
		}

	}

	void MainMenuState::draw()
	{
		_data->window.clear();

		for (int i = 0; i < _backgroundLayers.size(); i++)
		{
			_data->window.draw(_backgroundLayers[i]);
		}

		_data->window.draw(_title);
		_data->window.draw(_music);
		
		drawInstructions();

		_data->window.display();
	}

	void MainMenuState::initTitle()
	{
		_data->asset.loadFont("game font", "Resources/title3.TTF");
		_title.setFont(_data->asset.getFont("game font"));
		_title.setString("BANDIT RUSH");
		_title.setCharacterSize(49);
		_title.setPosition((_data->window.getSize().x - _title.getGlobalBounds().width) / 2, _data->window.getSize().y * 0.1f);
	}


	void MainMenuState::initSound()
	{
		// game sound on/off button
		_music.setTexture(_data->asset.getTexture("sound"));
		_music.setScale(0.8f, 0.8f);
		_music.setTextureRect(sf::IntRect(0, 0, 65, 60));
		_music.setPosition(_data->window.getSize().x - _music.getGlobalBounds().width - 5.0f, 5.0f);

		// play game sound
		_gameMusic.setBuffer(_data->asset.getSoundBuffer("game music"));
		_gameMusic.play();
		_gameMusic.setLoop(true);
	}


	void MainMenuState::initInstructions()
	{
		// instructions
		_data->asset.loadTexture("Keyboard", "Resources/Images/Keyboardkeys.png");
		grey = sf::Color(125, 125, 125);
		greyButton = sf::IntRect(34, 67, 30, 30);
		greySpace = sf::IntRect(3, 103, 154, 30);

		// PRESS KEYS
		_pressKeys.setFont(_data->asset.getFont("game font"));
		_pressKeys.setString("Press the keys below to continue");
		_pressKeys.setCharacterSize(14);
		_pressKeys.setPosition((_data->window.getSize().x - _pressKeys.getGlobalBounds().width) / 2, _data->window.getSize().y * 0.3f);

		// A
		_keyA.setTexture(_data->asset.getTexture("Keyboard"));
		_keyA.setTextureRect(sf::IntRect(2, 30, 30, 30));
		_keyA.setScale(2.0f, 2.0f);
		_keyA.setPosition(_data->window.getSize().x / 2 - _keyA.getGlobalBounds().width,
			(_data->window.getSize().y * 0.8f - _keyA.getGlobalBounds().height) / 2);

		_textA.setFont(_data->asset.getFont("game font"));
		_textA.setString("ATTACK");
		_textA.setCharacterSize(14);
		_textA.setFillColor(sf::Color::Black);
		_textA.setPosition(_data->window.getSize().x * 0.53f, _keyA.getGlobalBounds().top + _textA.getGlobalBounds().height * 1.3f);


		// D
		_keyD.setTexture(_data->asset.getTexture("Keyboard"));
		_keyD.setTextureRect(sf::IntRect(64, 30, 30, 30));
		_keyD.setScale(2.0f, 2.0f);
		_keyD.setPosition(_data->window.getSize().x / 2 - _keyD.getGlobalBounds().width,
			(_data->window.getSize().y - _keyD.getGlobalBounds().height) / 2);

		_textD.setFont(_data->asset.getFont("game font"));
		_textD.setString("DASH");
		_textD.setCharacterSize(14);
		_textD.setFillColor(sf::Color::Black);
		_textD.setPosition(_data->window.getSize().x * 0.53f, _keyD.getGlobalBounds().top + _textD.getGlobalBounds().height * 1.3f);


		// SPACE BAR
		_keySpace.setTexture(_data->asset.getTexture("Keyboard"));
		_keySpace.setTextureRect(sf::IntRect(96, 30, 154, 30));
		_keySpace.setScale(2.0f, 2.0f);
		_keySpace.setPosition(_data->window.getSize().x / 2 - _keySpace.getGlobalBounds().width,
			(_data->window.getSize().y * 1.2f - _keySpace.getGlobalBounds().height) / 2);

		_textSpace.setFont(_data->asset.getFont("game font"));
		_textSpace.setString("JUMP / FLIP");
		_textSpace.setCharacterSize(14);
		_textSpace.setFillColor(sf::Color::Black);
		_textSpace.setPosition(_data->window.getSize().x * 0.53f, _keySpace.getGlobalBounds().top + _textSpace.getGlobalBounds().height * 1.3f);

		// arrow keys

		// UP
		_arrowU.setTexture(_data->asset.getTexture("Keyboard"));
		_arrowU.setTextureRect(sf::IntRect(188, 72, 30, 30));
		_arrowU.setScale(2.0f, 2.0f);
		_arrowU.setPosition(_data->window.getSize().x / 2 - _keyD.getGlobalBounds().width, (_data->window.getSize().y * 1.4f - _keyD.getGlobalBounds().height) / 2);

		// DOWN
		_arrowD.setTexture(_data->asset.getTexture("Keyboard"));
		_arrowD.setTextureRect(sf::IntRect(188, 102, 30, 30));
		_arrowD.setScale(2.0f, 2.0f);
		_arrowD.setPosition(_arrowU.getGlobalBounds().left, _arrowU.getGlobalBounds().top + _arrowD.getGlobalBounds().height);

		// LEFT
		_arrowL.setTexture(_data->asset.getTexture("Keyboard"));
		_arrowL.setTextureRect(sf::IntRect(156, 102, 30, 30));
		_arrowL.setScale(2.0f, 2.0f);
		_arrowL.setPosition(_arrowU.getGlobalBounds().left - _arrowL.getGlobalBounds().width - 5.0f, _arrowD.getGlobalBounds().top);

		// RIGHT
		_arrowR.setTexture(_data->asset.getTexture("Keyboard"));
		_arrowR.setTextureRect(sf::IntRect(218, 102, 30, 30));
		_arrowR.setScale(2.0f, 2.0f);
		_arrowR.setPosition(_arrowU.getGlobalBounds().left + _arrowR.getGlobalBounds().width, _arrowD.getGlobalBounds().top);
	}

	void MainMenuState::drawInstructions()
	{
		_data->window.draw(_pressKeys);

		// A
		_data->window.draw(_keyA);
		_data->window.draw(_textA);
		// D
		_data->window.draw(_keyD);
		_data->window.draw(_textD);
		// SPACE
		_data->window.draw(_keySpace);
		_data->window.draw(_textSpace);
		// ARROWS
		_data->window.draw(_arrowU);
		_data->window.draw(_arrowD);
		_data->window.draw(_arrowL);
		_data->window.draw(_arrowR);
	}

	void MainMenuState::greyKey(sf::Sprite& key)
	{
		key.setTextureRect(greyButton);
	}

	void MainMenuState::greyText(sf::Text text)
	{
		text.setFillColor(grey);
	}
}