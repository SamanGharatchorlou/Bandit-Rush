#pragma once

#include <SFML/Graphics.hpp>

namespace environment
{
	class Layer
	{
	private:
		sf::Texture _texture;
		sf::Sprite _sprite;

		int _texturePixleWidth;
		int _texturePixleHeight;

		int _pixleSize;
		int _firstTile;

		void loadTexture(std::string filePath);
		void setPixleSize(int pixleSize);

		sf::IntRect getRectAt(int x, int y);

	public:
		Layer(std::string filePath, int pixleSize, int firstTile);
		sf::Vector2i decode(int code);

		int getFirstTile();

		sf::Sprite getPixleAt(int x, int y);
	};
}