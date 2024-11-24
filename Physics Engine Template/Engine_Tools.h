#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Engine_Tools
{
private:
	void ProjectVerticesToAxis(std::vector<sf::Vector2f> vertices, sf::Vector2f axis, float& min, float& max); // projects an array of vertices to an axis and find if theres an overlap
	float DotProduct(sf::Vector2f a, sf::Vector2f b) { return a.x * b.x + a.y * b.y; } // find the dot product of two vectors

public:
	sf::Clock clock;
	sf::Time deltaTime;			// Delta time
	float dtMultiplier = 30.0f; // Delta time multiplier

	// Uses separating axis theorem to check if two polygons are colliding
	bool SATPolygonCollision(std::vector<sf::Vector2f> verticesA, std::vector<sf::Vector2f> verticesB);

	Engine_Tools();
	~Engine_Tools();
};

