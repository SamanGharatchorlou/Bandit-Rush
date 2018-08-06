#pragma once
#include <SFML/Graphics.hpp>

namespace environment
{
	class StatScreen
	{
	private:
		sf::RenderWindow* _window;

		sf::Texture _texture;
		sf::Sprite _heart;

		sf::Font _font;
		sf::Text _text;

	public:
		void loadStatScreen(sf::RenderWindow& window);
		void loadSprites();
		void loadFonts();

		void drawHealth(int health);
		void drawKills(int kills);
	};
}