#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Engine_Tools
{
public:
	sf::Clock clock;
	sf::Time deltaTime;
	float dtMultiplier = 30.0f;

	bool DetectCollisionCircleToRectangle(sf::CircleShape circle, sf::RectangleShape rectangle);

	Engine_Tools();
	~Engine_Tools();
};

