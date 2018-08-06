#pragma once
#include "Layer.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

namespace environment
{
	typedef std::vector<Layer*> Layers;

	class MapDecoder
	{
	private:
		sf::RenderWindow& _window;

		int _width;
		int _height;
		int _pixleSize;

		sf::Texture _texture, bgTexture, fgTexture;
		sf::Sprite _sprite;

		Layers _layers;

		Layers subVector(Layers layers, int startingLayer, int layerCount);

		void decodeXML(int* encodingArray, Layer* layer);
		void decodeXML(int* encodingArray, Layers layers);

		sf::Vector2f drawingPosition(int encoding);
		sf::Sprite getPixle(Layer* layer, int code);

		void releaseLayers();

	public:
		MapDecoder(sf::RenderWindow& window, int pixleSize);

		void buildBackgroundLayers();

		sf::Sprite compressLayers();

		sf::Sprite backgroundLayer();

		sf::Sprite& getSprite() { return _sprite; }
	};
}
