#include "GameController.h"
#include "Player.h"

namespace srac
{
	GameController::GameController(gameDataRef data) : _data(data)
	{
		srand(time(NULL));

		arrowShower = new ArrowShower(_data);

		warningTime = 2.5f;
		showerTime = 4.0f;
		fallTime = 2.0f;
		showerCooldown = 2.0f;

		// warning text
		font.loadFromFile("Resources/title2.TTF");

		warningText.setFont(font);
		warningText.setCharacterSize(28);
		warningText.setString("ARROW SHOWER \n INCOMMING!!!");
		warningText.setFillColor(sf::Color(0, 0, 0, 0));

		_flashing = false;
		_changeRate = 10;
	}


	void GameController::releaseArrows(float time, float dt)
	{
		float timer = showerTimer.getElapsedTime().asSeconds();

		// warning
		if (timer < warningTime)
		{
			_flashing = true;
			flashWarning();
		}
		// arrow shower
		else if (timer < warningTime + showerTime)
		{
			resetWarning();

			arrowShower->arrowShower(showerTime, dt);
			arrowShower->fall(dt);

			if(timer > warningTime + 0.5f)
				checkArrowHit();
		}
		// falling only
		else if (timer < warningTime + showerTime + fallTime)
		{
			arrowShower->fall(dt);

			checkArrowHit();
		}
		// end
		else if(timer > warningTime + showerTime + fallTime + showerCooldown)
		{
			arrowShower->endShower();
			showerTimer.restart();

			levelChosen = false;	
			_hasHit = false;
		}
	}

	void GameController::checkArrowHit()
	{
		sf::Vector2f position = _data->player->getPlayerData()->attributes.getPosition();

		if (!_hasHit)
		{
			if (arrowShower->inNoMansLand(position))
			{
				_data->player->getPlayerData()->attributes.setTakingDmg(true);
				_hasHit = true;
			}
		}
	}

	void GameController::showerLocation()
	{
		if (!levelChosen)
		{
			int randLevel = rand() % arrowShower->levelCount();

			warningTime = randLevel == 0 ? 7.0f : 2.0f;

			prepareShower(randLevel);

			levelChosen = true;
		}
	}


	void GameController::prepareShower(int level)
	{
		arrowShower->showerRange(level);
		warningPosition();
	}


	void GameController::warningPosition()
	{
		float xLeft = arrowShower->getRangeH()[0];
		float xRight = arrowShower->getRangeH()[1];

		float top = arrowShower->getRangeV()[0];
		float bot = arrowShower->getRangeV()[1];

		warningText.setPosition( xLeft + (xRight - xLeft - warningText.getGlobalBounds().width) / 2.0f, 
			top + (bot - top - warningText.getGlobalBounds().height) / 2.0f);
	}


	void GameController::flashWarning()
	{
		int alpha = warningText.getFillColor().a;

		if (alpha > 255 - _changeRate)
		{
			_flashDirection = -1;
		}
		else if (alpha <= _changeRate)
		{
			_flashDirection = 1;
		}

		warningText.setFillColor(sf::Color(255, 0, 0, alpha + _flashDirection * _changeRate));
	}


	void GameController::resetWarning()
	{
		_flashing = false;
		warningText.setFillColor(sf::Color(0, 0, 0, 0));
		_flashDirection = 1;
	}


	void GameController::draw()
	{
		arrowShower->drawArrows();

		if(_flashing)
			_data->window.draw(warningText);
	}
}