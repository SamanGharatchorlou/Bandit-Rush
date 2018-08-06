#include "ArrowShower.h"

#include <iostream>

namespace srac
{
	ArrowShower::ArrowShower(gameDataRef data) : _data(data)
	{
		_fallSpeed = 250.0f;
		_waveCounter = 0;

		quiver.push_back(arrow0);
		quiver.push_back(arrow1);
		quiver.push_back(arrow2);
		quiver.push_back(arrow3);
		quiver.push_back(arrow4);
		quiver.push_back(arrow5);
		quiver.push_back(arrow6);
		quiver.push_back(arrow7);
		quiver.push_back(arrow8);
		quiver.push_back(arrow9);

		for (int i = 0; i < quiver.size(); i++)
		{
			quiver[i].setTexture(_data->asset.getTexture("arrow" + std::to_string(i)));
		}

		int buff = 25.0f;

		// top to bot
		_levels = 
		{ 
			{LEVEL_02 + buff * 3, LEVEL_01 + buff},
			{LEVEL_02 + buff , LEVEL_01 + buff}, 
		    {LEVEL_02 + buff , LEVEL_01 + buff }, 
		    {0, LEVEL_02 + buff}, 
		    {0, LEVEL_03 + buff} 
		};

		// left to right
		_ranges = 
		{ 
			{ 0, WINDOW_WIDTH},
			{0, WINDOW_WIDTH / 2.0f},
			{WINDOW_WIDTH / 2.0f, WINDOW_WIDTH},
			{0, WINDOW_WIDTH / 2.0f},
			{WINDOW_WIDTH / 2.0f, WINDOW_WIDTH}
		};
	}


	void ArrowShower::showerRange(int level)
	{
		_vRange = _levels[level];
		_hRange = _ranges[level];
	}


	// main shower, spawn and fall
	void ArrowShower::arrowShower(float freq, float dt)
	{
		// every T seconds spawn new arrow wave
		if (_waveTimer.getElapsedTime().asSeconds() > float(1.0f / freq))
		{
			arrowPositions.push_back(arrowWave(_ranges[0][0]));
			_waveCounter++;
			_waveTimer.restart();
		}
	}

	// create list of arrow positions (1 wave / row)
	std::vector<std::vector<float>> ArrowShower::arrowWave(int level)
	{
		int arrowSpace = 25.0f;
		int shift = _waveCounter % 2 == 0 ? 0 : 1;

		float x = _hRange[0] + shift * arrowSpace / 2;

		std::vector<std::vector<float>> wave;

		while (x < _hRange[1])
		{
			wave.push_back(std::vector<float>{ x, _vRange[0]});
			x += arrowSpace;
		}

		return wave;
	}


	// spawn single arrow sprite
	sf::Sprite ArrowShower::arrow(float x, float y)
	{
		// get random arrow
		sf::Sprite arrow = quiver[rand() % quiver.size()];

		arrow.setPosition(x, y);
		arrow.setRotation(-135.0f);

		return arrow;
	}


	void ArrowShower::fall(float dt)
	{
		for(int i = 0; i < arrowPositions.size(); i++)
		{
			// shop out of bounds arrow wave
			if (arrowPositions[i][0][1] > _vRange[1])
				continue;

			// add movement to y position
			for (int j = 0; j < arrowPositions[i].size(); j++)
			{
				arrowPositions[i][j][1] += _fallSpeed * dt;
			}
		}
	}


	void ArrowShower::endShower()
	{
		arrowPositions.clear();
	}


	void ArrowShower::drawArrows()
	{
		for (int i = 0; i < arrowPositions.size(); i++)
		{
			// shop out of bounds arrow wave
			if (arrowPositions[i][0][1] > _vRange[1])
				continue;

			for (int j = 0; j < arrowPositions[i].size(); j++)
			{
				_data->window.draw(arrow(arrowPositions[i][j][0], arrowPositions[i][j][1]));
			}
		}
	}

	int ArrowShower::levelCount()
	{
		return _levels.size();
	}


	bool ArrowShower::inNoMansLand(sf::Vector2f playerPosition)
	{
		sf::IntRect noMansLand = sf::IntRect(_hRange[0], _vRange[0], _hRange[1] - _hRange[0], _vRange[1] - _vRange[0]);

		if (noMansLand.contains(sf::Vector2i(playerPosition)))
		{
			return true;
		}

		return false;
	}
}