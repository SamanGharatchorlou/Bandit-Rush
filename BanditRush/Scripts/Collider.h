#pragma once
#include "Player.h"


#include <SFML/Graphics.hpp>
#include <vector>

namespace environment
{
	typedef sf::Rect<int> Box;

	class Collider
	{
	private:
		std::vector<Box> _collisionBoxes;

		sf::Vector2i _playerOrigin;

		bool collisions(Box collider);
		std::vector<Box> collidedBoxes(Box collider);

		void addCollisionBox(int x, int y, int width, int height);
		sf::Vector2i toVec2i(sf::Vector2f floatVector);

	public:
		Collider();

		bool colliding(srac::playerDataRef player, sf::Vector2f movement);
		bool sideWall(srac::playerDataRef player, sf::Vector2f movement);
		bool falling(srac::playerDataRef player, sf::Vector2f movement);
		bool grounded(srac::playerDataRef player, sf::Vector2f movement);

		void setLevel01();

		Box getBoxCollider(sf::Vector2f Position, sf::Vector2f size);
		Box getBox(sf::Vector2f position, float range);
	};
}