#include "InputManager.h"

namespace srac
{
	bool InputManager::isSpriteClicked(sf::Sprite sprite, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect rect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

			if (rect.contains(sf::Mouse::getPosition(window)))
				return true;
		}

		return false;
	}
}