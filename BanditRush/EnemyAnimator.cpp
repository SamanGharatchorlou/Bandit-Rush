#include "EnemyAnimator.h"
#include <iostream>

namespace srac
{
	EnemyAnimator::EnemyAnimator() 
	{
		loadSpriteSheet();
		configureAnimations();
		spriteDimentions(6, 5);
	}

	void EnemyAnimator::playLoop(float speed)
	{
		if (_clipTimer.getElapsedTime().asSeconds() > 1.0f / speed)
		{
			nextClip();
			_activeClip = getActiveClip();

			_clipTimer.restart();
		}
	}

	bool EnemyAnimator::playSingle(float speed)
	{
		if (_clipTimer.getElapsedTime().asSeconds() > 1.0f / speed)
		{
			if (_stopped)
			{
				_animationIndex = _startingIndex + _clipCount - 1;
				return true;
			}

			int thisClip = _animationIndex;

			nextClip();

			if (_animationIndex < thisClip)
			{
				_stopped = true;
				return true;
			}

			_activeClip = getActiveClip();
			_clipTimer.restart();
		}

		return false;
	}


	bool EnemyAnimator::partComplete(float speed, float percentComplete)
	{
		// animation time > % total animation time
		if (_animationTimer.getElapsedTime().asSeconds() > (percentComplete / 100.0f) * (_clipCount / speed))
		{
			//_animationTimer.restart();
			return true;
		}

		return false;
	}


	// [name] = {starting index, clip count}
	void EnemyAnimator::configureAnimations()
	{
		// Djinn Bandit 
		_animationCode["idle"] = { 1, 4 };
		_animationCode["run"] = { 5, 6 };
		_animationCode["attack"] = { 11, 5 };
		_animationCode["hurt"] = { 16, 3 };
		_animationCode["die"] = { 19, 9 };
	}


	void EnemyAnimator::newAnimation(std::string name)
	{
		_startingIndex = _animationCode[name][0];
		_clipCount = _animationCode[name][1];

		_animationIndex = _startingIndex;
		_stopped = false;
	}


	void EnemyAnimator::loadSpriteSheet() 
	{
		sf::Texture texture;

		if(texture.loadFromFile("Resources/Images/Enemies/djinn-bandit-Sheet.png"))
			_spriteSheet = texture;
	}


	void EnemyAnimator::spriteDimentions(int xCount, int yCount)
	{
		_xCount = xCount;
		_yCount = yCount;

		_spriteWidth = _spriteSheet.getSize().x / xCount;
		_spriteHeight = _spriteSheet.getSize().y / yCount;
	}


	sf::Texture& EnemyAnimator::getSpriteSheet()
	{
		return _spriteSheet;
	}


	sf::IntRect EnemyAnimator::getActiveClip()
	{
		int index = _animationIndex;
		int x, y = 0;

		while (index > _xCount)
		{
			y++;
			index -= _xCount;
		}

		x = index - 1;

		return sf::IntRect(_spriteWidth * x, _spriteHeight * y, _spriteWidth, _spriteHeight);
	}


	void EnemyAnimator::nextClip()
	{
		_animationIndex = (_animationIndex == _startingIndex + _clipCount - 1) ? _startingIndex : _animationIndex + 1;
	}

	void EnemyAnimator::resetClock()
	{
		_animationTimer.restart();
	}

}