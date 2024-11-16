#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Engine_Tools
{
private:
	void ProjectVerticesToAxis(std::vector<sf::Vector2f> vertices, sf::Vector2f axis, float& min, float& max);
	float DotProduct(sf::Vector2f a, sf::Vector2f b) { return a.x * b.x + a.y * b.y; }

public:
	sf::Clock clock;
	sf::Time deltaTime;
	float dtMultiplier = 30.0f;

	bool SATPolygonCollision(std::vector<sf::Vector2f> verticesA, std::vector<sf::Vector2f> verticesB);

	Engine_Tools();
	~Engine_Tools();
};

