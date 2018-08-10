#pragma once
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace srac
{
	class ArrowShower
	{
	private:
		gameDataRef _data;

		std::vector<sf::Sprite> quiver;
		sf::Sprite arrow0, arrow1, arrow2, arrow3, arrow4, arrow5, arrow6, arrow7, arrow8, arrow9;

		std::vector<std::vector<float>> _levels, _ranges;
		std::vector<float> _vRange, _hRange;

		//vector[arrow wave][arrow][position x,y]
		std::vector<std::vector<std::vector<float>>> arrowPositions;

		int _waveCounter;
		float _fallSpeed;

		sf::Clock _waveTimer;

		std::vector<std::vector<float>> arrowWave(int level);
		sf::Sprite arrow(float x, float y);

	public:
		ArrowShower(gameDataRef data);
			
		void showerRange(int level);
		void arrowShower(float freq, float dt);
		void fall(float dt);
		void endShower();

		std::vector<float> getRangeH() { return _hRange; }
		std::vector<float> getRangeV() { return _vRange; }

		int levelCount();

		bool inNoMansLand(sf::Vector2f playerPosition);

		void drawArrows();
	};
}