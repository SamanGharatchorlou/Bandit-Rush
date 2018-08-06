#include "GameOverState.h"
#include "GameState.h"

#include <fstream>
#include <iostream>

namespace srac
{
	GameOverState::GameOverState(gameDataRef data, int score) : _data(data), _score(score) {  }

	void GameOverState::init()
	{
		addnewScore();
		updateScoreBoard();

		// background
		mapDecoder = new environment::MapDecoder(_data->window, 16);

		mapDecoder->buildBackgroundLayers();
		map = mapDecoder->backgroundLayer();

		// play button
		_data->asset.loadTexture("play button", "Resources/Images/PlayButton.png");
		_play.setTexture(_data->asset.getTexture("play button"));
		_play.setScale(0.1f, 0.1f);

		_play.setPosition(_data->window.getSize().x / 2 - _play.getGlobalBounds().width / 2.0f, _data->window.getSize().y * 1.3f / 2);
		

		// score text
		scoreText.setFont(_data->asset.getFont("main"));
		scoreText.setCharacterSize(42);
		scoreText.setFillColor(sf::Color::Black);
		scoreText.setString("Score: " + std::to_string(_score));

		scoreText.setOrigin(scoreText.getGlobalBounds().width / 2.0f, scoreText.getGlobalBounds().height / 2.0f);
		scoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().y * 0.7f / 2);

		// high score text
		highScoreText.setFont(_data->asset.getFont("main"));
		highScoreText.setCharacterSize(35);
		highScoreText.setFillColor(sf::Color::Black);
		highScoreText.setString("High Score: " + std::to_string(scoreBoard[0]));

		highScoreText.setOrigin(highScoreText.getGlobalBounds().width / 2.0f, highScoreText.getGlobalBounds().height / 2.0f);
		highScoreText.setPosition(_data->window.getSize().x / 2, _data->window.getSize().y * 1.1f / 2);
	}

	void GameOverState::handleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				_data->window.close();
			}

			if (_data->input.isSpriteClicked(_play, sf::Mouse::Left, _data->window))
			{
				_data->machine.replaceState(stateRef(new GameState(_data)));
			}

		}
	}


	void GameOverState::draw()
	{
		_data->window.clear();

		_data->window.draw(map);
	
		_data->window.draw(scoreText);
		_data->window.draw(highScoreText);

		_data->window.draw(_play);

		_data->window.display();
	}




	void GameOverState::updateScoreBoard()
	{
		// read scores from file
		std::fstream rFile("Resources/scores.txt", std::fstream::in);
		std::string tempScore, scoreString;

		if (rFile.is_open())
		{
			while (!rFile.eof())
				rFile >> scoreString;
		}
		rFile.close();

		// build score board from scoreString
		for (int i = 0; i < scoreString.length(); i++)
		{
			if (scoreString[i] == ',')
			{
				scoreBoard.push_back(std::stoi(tempScore));
				tempScore = "";
			}
			else
			{
				tempScore += scoreString[i];
			}
		}

		// sort and dedupe scores
		std::sort(scoreBoard.rbegin(), scoreBoard.rend());
		scoreBoard.erase(std::unique(scoreBoard.begin(), scoreBoard.end()), scoreBoard.end());

		scoreString = "";
		for (int i = 0; i < scoreBoard.size(); i++)
		{
			scoreString += std::to_string(scoreBoard[i]) + ",";
		}

		//overwrite file with new score board
		std::fstream wFile("Resources/scores.txt", std::fstream::out | std::fstream::trunc);

		if (wFile.is_open())
			wFile << scoreString;

		wFile.close();
	}


	// update file with new score
	void GameOverState::addnewScore()
	{
		std::fstream wFile("Resources/scores.txt", std::fstream::out | std::fstream::app);

		if (wFile.is_open())
			wFile << _score << ",";

		wFile.close();
	}

}