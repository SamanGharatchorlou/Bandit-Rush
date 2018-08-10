#include "StatScreen.h"

namespace environment
{
	void StatScreen::loadStatScreen(sf::RenderWindow& window)
	{
		_window = &window;

		loadSprites();
		loadFonts();
	}

	void StatScreen::loadSprites()
	{
		if (_texture.loadFromFile("Resources/Images/heart.png"))
			_heart.setTexture(_texture);

		_heart.setScale(0.1f, 0.1f);
	}

	void StatScreen::loadFonts()
	{
		_font.loadFromFile("Resources/title2.TTF");

		_text.setFont(_font);
		_text.setCharacterSize(21);
		_text.setString("Kills : 0");
		_text.setFillColor(sf::Color::Red);
		_text.setPosition(_window->getSize().x / 2.0f - _text.getGlobalBounds().width / 2.0f, 10.0f);
	}

	void StatScreen::drawHealth(int health)
	{
		for (int i = 0; i < health; i++)
		{
			_heart.setPosition(_heart.getGlobalBounds().width * i, 0);
			_window->draw(_heart);
		}
	}

	void StatScreen::drawKills(int kills)
	{
		_text.setString("Kills : " + std::to_string(kills));
		_window->draw(_text);
	}

}