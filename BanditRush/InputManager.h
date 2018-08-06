#pragma once

#include <SFML/Graphics.hpp>

namespace srac
{
	struct InputManager
	{
		bool isSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window);
	};

}
