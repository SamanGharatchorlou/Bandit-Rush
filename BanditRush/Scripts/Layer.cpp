#include "Layer.h"

namespace environment
{
	Layer::Layer(std::string filePath, int pixleSize, int firstTile) : _pixleSize(pixleSize), _firstTile(firstTile)
	{
		loadTexture(filePath);
		setPixleSize(pixleSize);
	}


	void Layer::loadTexture(std::string filePath)
	{
		_texture.loadFromFile(filePath);
		_sprite.setTexture(_texture);
	}

	void Layer::setPixleSize(int pixleSize)
	{
		_texturePixleWidth = _texture.getSize().x / pixleSize;
		_texturePixleHeight = _texture.getSize().y / pixleSize;
	}

	// xml code to image tile position
	sf::Vector2i Layer::decode(int code)
	{
		int x = 0;
		int y = 0;

		while (code > _texturePixleWidth)
		{
			code -= _texturePixleWidth;
			y++;
		}

		x = code - 1;

		return sf::Vector2i(x, y);
	}

	int Layer::getFirstTile()
	{
		return _firstTile;
	}



	sf::Sprite Layer::getPixleAt(int x, int y)
	{
		_sprite.setTextureRect(getRectAt(x, y));

		return _sprite;
	}

	sf::IntRect Layer::getRectAt(int x, int y)
	{
		sf::Vector2i rectPosition = sf::Vector2i(x, y) * _pixleSize;
		sf::Vector2i rectSize = sf::Vector2i(1, 1) * _pixleSize;

		return sf::IntRect(rectPosition, rectSize);
	}

}