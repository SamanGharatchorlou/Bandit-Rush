#include "Collider.h"
#include "DEFINITIONS.h"
#include <iostream>

namespace environment
{
	Collider::Collider() 
	{
		_playerOrigin = sf::Vector2i(CHARACTER_WIDTH / 2, CHARACTER_HEIGHT);
	}

	void Collider::addCollisionBox(int x, int y, int width, int height)
	{
		_collisionBoxes.push_back(Box(x, y, width, height));
	}


	bool Collider::collisions(Box collider)
	{
		for (int i = 0; i < _collisionBoxes.size(); i++)
		{
			if (collider.intersects(_collisionBoxes[i]))
				return true;
		}

		return false;
	}

	// returns all collision boxes being collided with
	std::vector<Box> Collider::collidedBoxes(Box collider)
	{
		std::vector<Box> boxes;

		for (int i = 0; i < _collisionBoxes.size(); i++)
		{
			if (collider.intersects(_collisionBoxes[i]))
				boxes.push_back(_collisionBoxes[i]);
		}

		return boxes;
	}


	bool Collider::grounded(srac::playerDataRef player, sf::Vector2f movement)
	{
		// ceil round movement to prevent loss of information
		sf::Vector2i position = sf::Vector2i(player->attributes.getPosition()) - _playerOrigin + sf::Vector2i(0, movement.y);
		sf::Vector2i playerSize = sf::Vector2i(CHARACTER_WIDTH, CHARACTER_HEIGHT);

		// player collider and box of object colliding with
		Box playerCollider = Box(position, playerSize);
		std::vector<Box> collisionBoxes = collidedBoxes(playerCollider);

		for (int i = 0; i < collisionBoxes.size(); i++)
		{
			// add small movement buffer to check
			if (player->attributes.getPosition().y - ceil(movement.y) < collisionBoxes[i].top)
			{
				player->attributes.setPosition(player->attributes.getPosition().x, collisionBoxes[i].top);
				return true;
			}
		}

		return false;
	}


	bool Collider::falling(srac::playerDataRef player, sf::Vector2f movement)
	{
		sf::Vector2i playerPosition = sf::Vector2i(player->attributes.getPosition()) - _playerOrigin + toVec2i(movement);
		sf::Vector2i playerSize = sf::Vector2i(CHARACTER_WIDTH * 0.9, CHARACTER_HEIGHT);

		return !collisions(Box(playerPosition, playerSize));
	}

	//TODO: change animate getTexture() to a reference!!!!


	bool Collider::colliding(srac::playerDataRef player, sf::Vector2f movement)
	{
		// top left point of character (NOT of texture/sprite!) + movement
		sf::Vector2i playerPosition = sf::Vector2i(player->attributes.getPosition()) - _playerOrigin + toVec2i(movement);
		sf::Vector2i playerSize = sf::Vector2i(CHARACTER_WIDTH, CHARACTER_HEIGHT);

		return collisions(Box(playerPosition, playerSize));
	}

	void Collider::setLevel01()
	{
		_collisionBoxes.clear();
		
		// Floor
		addCollisionBox(0, LEVEL_01, 1024, 34);
		addCollisionBox(0, LEVEL_02, 405, 63);
		addCollisionBox(640, LEVEL_03, 384, 65);

		// edges
		addCollisionBox(1020, 0, 8, WINDOW_HEIGHT);
		addCollisionBox(-4, 0, 8, WINDOW_HEIGHT);

		// rocks
		addCollisionBox(543, 478, 84, 13);

		addCollisionBox(0, 336, 32, 13);

		addCollisionBox(994, 625, 31, 13);

		addCollisionBox(0, 95, 67, 13);

		addCollisionBox(734, 512, 86, 13);
		addCollisionBox(880, 561, 47, 13);
		addCollisionBox(432, 449, 47, 13);
		addCollisionBox(129, 337, 47, 13);

		addCollisionBox(681, 602, 47, 7);
		addCollisionBox(429, 254, 87, 13);


		addCollisionBox(272, 289, 47, 13);
		addCollisionBox(576, 241, 47, 13);
	}

	sf::Vector2i Collider::toVec2i(sf::Vector2f floatVector)
	{
		return sf::Vector2i(ceil(floatVector.x), ceil(floatVector.y));
	}

	Box Collider::getBoxCollider(sf::Vector2f position, sf::Vector2f size)
	{
		sf::Vector2i boxPosition = sf::Vector2i(position.x - size.x / 2, position.y - size.y);
		sf::Vector2i boxSize = sf::Vector2i(size);

		return Box(boxPosition, boxSize);
	}

	Box Collider::getBox(sf::Vector2f position, float range)
	{
		return Box(sf::Vector2i(position), sf::Vector2i(range, range));
	}
}
