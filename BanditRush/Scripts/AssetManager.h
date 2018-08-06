#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>
#include <vector>

namespace srac
{
	class AssetManager
	{
	private:
		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;
		std::map<std::string, sf::SoundBuffer> _sounds;

		sf::Sprite bgLayer1, bgLayer2, bgLayer3, bgLayer4;
		std::vector<sf::Sprite> backgroundLayers{ bgLayer1, bgLayer2, bgLayer3, bgLayer4 };

	public:
		AssetManager();

		// textures
		void loadTexture(std::string name, std::string filePath);
		sf::Texture& getTexture(std::string name);

		void fitToScreen(sf::Sprite& sprite, sf::Vector2u windowSize);
		std::vector<sf::Sprite> getBackgroundLayers();

		// fonts
		void loadFont(std::string name, std::string filePath);
		sf::Font& getFont(std::string name);

		// sounds
		void loadSound(std::string name, std::string filePath);
		sf::SoundBuffer& getSoundBuffer(std::string name);

	};
}