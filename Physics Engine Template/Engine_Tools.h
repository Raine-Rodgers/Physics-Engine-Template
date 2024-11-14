#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Engine_Tools
{
public:
	sf::Clock clock;
	sf::Time deltaTime;
	float dtMultiplier = 30.0f;

	void DetectCollisionCircleToCircle(sf::CircleShape* circle1, sf::CircleShape* circle2);
	bool IntersectPolygons(sf::Vector2f poly1, sf::Vector2f poly2);

	Engine_Tools();
	~Engine_Tools();
};

