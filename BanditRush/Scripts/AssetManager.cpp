#include "AssetManager.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace srac
{
	AssetManager::AssetManager()
	{
		// --- SOUNDS ---

		// game sound
		loadSound("game music", "Resources/Sounds/Timpani and Brass.wav");

		// player attack 1(air), 2(air) & 3(hit)
		loadSound("attack 1", "Resources/Sounds/attack1.flac");
		loadSound("attack 2", "Resources/Sounds/attack2.wav");
		loadSound("attack 3", "Resources/Sounds/attack3.wav");

		// enemy attack
		loadSound("enemy attack", "Resources/Sounds/EnemyAttack.wav");

		// ouch
		loadSound("ouch", "Resources/Sounds/ouch.wav");

		// dash
		loadSound("woosh", "Resources/Sounds/woosh2.flac");

		//jump
		loadSound("jump", "Resources/Sounds/jump.wav");
		loadSound("flip", "Resources/Sounds/flip.wav");

		// --- IMAGES ---

		// sound on / off
		loadTexture("sound", "Resources/Images/Music_on_off.png");

		// dash
		loadTexture("multi image", "Resources/Images/MainCharacter/adventurer-run2-00.png");

		// arrows
		loadTexture("arrow0", "Resources/Images/Items/arrow_01a.png");
		loadTexture("arrow1", "Resources/Images/Items/arrow_01b.png");
		loadTexture("arrow2", "Resources/Images/Items/arrow_01c.png");
		loadTexture("arrow3", "Resources/Images/Items/arrow_01d.png");
		loadTexture("arrow4", "Resources/Images/Items/arrow_01e.png");
		loadTexture("arrow5", "Resources/Images/Items/arrow_02a.png");
		loadTexture("arrow6", "Resources/Images/Items/arrow_02b.png");
		loadTexture("arrow7", "Resources/Images/Items/arrow_02c.png");
		loadTexture("arrow8", "Resources/Images/Items/arrow_02d.png");
		loadTexture("arrow9", "Resources/Images/Items/arrow_02e.png");



		// --- FONTS ---
		loadFont("main", "Resources/title2.TTF");
	}

	// textures
	void AssetManager::loadTexture(std::string name, std::string filePath)
	{
		sf::Texture texture;

		if (texture.loadFromFile(filePath))
			_textures[name] = texture;
	}

	sf::Texture& AssetManager::getTexture(std::string name)
	{
		return _textures[name];
	}

	void AssetManager::fitToScreen(sf::Sprite& sprite, sf::Vector2u windowSize)
	{
		sprite.setScale(windowSize.x / sprite.getGlobalBounds().width,
			windowSize.y / sprite.getGlobalBounds().height);
	}

	std::vector<sf::Sprite> AssetManager::getBackgroundLayers()
	{
		loadTexture("bg layer 1", "Resources/Images/Backgrounds/CloudsBack.png");
		loadTexture("bg layer 2", "Resources/Images/Backgrounds/CloudsFront.png");
		loadTexture("bg layer 3", "Resources/Images/Backgrounds/BGBack.png");
		loadTexture("bg layer 4", "Resources/Images/Backgrounds/BGFront.png");

		for (int i = 0; i < backgroundLayers.size(); i++)
		{
			backgroundLayers[i].setTexture(getTexture("bg layer " + std::to_string(i + 1)));
			fitToScreen(backgroundLayers[i], sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
		}

		return backgroundLayers;
	}

	// fonts
	void AssetManager::loadFont(std::string name, std::string filePath)
	{
		sf::Font font;

		if (font.loadFromFile(filePath))
			_fonts[name] = font;
	}

	sf::Font& AssetManager::getFont(std::string name)
	{
		return _fonts[name];
	}

	// sounds
	void AssetManager::loadSound(std::string name, std::string filePath)
	{
		sf::SoundBuffer soundBuff;

		if (!_sounds.count(name) && soundBuff.loadFromFile(filePath))
			_sounds[name] = soundBuff;
	}

	sf::SoundBuffer& AssetManager::getSoundBuffer(std::string name)
	{

		return _sounds[name];
	}
}