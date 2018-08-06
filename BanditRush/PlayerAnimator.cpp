#include "PlayerAnimator.h"
#include <iostream>

namespace srac
{
	PlayerAnimator::PlayerAnimator()
	{
		loadSpriteSheet("1.5", 	"Resources/Images/MainCharacter/SpriteSheets/adventurer-v1.5-Sheet.png");
		loadSpriteSheet("hand combat", "Resources/Images/MainCharacter/SpriteSheets/adventurer-hand-combat-Sheet.png");
		configureAnimations();
	}

	void PlayerAnimator::activateSheetFor(std::string animationName)
	{
		// hand combat sheet
		if (animationName == "dash" || animationName == "hurt" || animationName == "die")
		{
			_spriteSheet = _spriteSheets["hand combat"];
			sheetDimentions(7, 10);
		}
		// 1.5 sheet
		else
		{
			_spriteSheet = _spriteSheets["1.5"];
			sheetDimentions(7, 16);
		}
	}


	void PlayerAnimator::playLoop(float speed)
	{
		if (_clipTimer.getElapsedTime().asSeconds() > 1.0f / speed)
		{
			nextClip();
			_activeClip = getActiveClip();

			_clipTimer.restart();
		}
	}

	bool PlayerAnimator::playSingle(float speed)
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


	bool PlayerAnimator::partComplete(float speed, float percentComplete)
	{
		// animation time > % total animation time
		if (_animationTimer.getElapsedTime().asSeconds() > (percentComplete / 100.0f) * (_clipCount / speed))
		{
			return true;
		}

		return false;
	}


	// [name] = {starting index, clip count}
	void PlayerAnimator::configureAnimations()
	{
		// 1.5
		_animationCode["idle"] = { 1, 4 };
		_animationCode["run"] = { 9, 6 };
		_animationCode["attack1"] = { 43, 5 };
		_animationCode["attack2"] = { 48, 6 };
		_animationCode["attack3"] = { 54, 6 };
		_animationCode["jump"] = { 15, 4 };
		_animationCode["fall"] = { 23, 2 };
		_animationCode["flip"] = { 19, 4 };

		// hand combat
		_animationCode["dash"] = { 62, 3 };
		_animationCode["hurt"] = { 33, 2 };
		_animationCode["die"] = { 33, 7 };
	}


	void PlayerAnimator::newAnimation(std::string name)
	{
		_startingIndex = _animationCode[name][0];
		_clipCount = _animationCode[name][1];

		_animationIndex = _startingIndex;
		_stopped = false;
	}

	void PlayerAnimator::loadSpriteSheet(std::string name, std::string filePath)
	{
		sf::Texture texture;

		if (texture.loadFromFile(filePath))
			_spriteSheets[name] = texture;
	}

	void PlayerAnimator::sheetDimentions(int xCount, int yCount)
	{
		_xCount = xCount;
		_yCount = yCount;

		// annoying extra 35 pixles on right side of sprite sheet...
		_spriteWidth = (_spriteSheet.getSize().x - 35) / xCount;
		_spriteHeight = _spriteSheet.getSize().y / yCount;
	}


	sf::Texture& PlayerAnimator::getSpriteSheet()
	{
		return _spriteSheet;
	}


	sf::IntRect PlayerAnimator::getActiveClip()
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


	void PlayerAnimator::nextClip()
	{
		_animationIndex = (_animationIndex == _startingIndex + _clipCount - 1) ? _startingIndex : _animationIndex + 1;
	}

	void PlayerAnimator::resetClock()
	{
		_animationTimer.restart();
	}

}