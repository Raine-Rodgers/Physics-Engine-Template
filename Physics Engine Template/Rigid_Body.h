#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Rigid_Body
{
protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
	float friction;
	bool lockedPosition;

public:
	Rigid_Body();
	Rigid_Body(sf::Vector2f acceleration, sf::Vector2f velocity,float mass, float friction, bool lockedPosition);
	~Rigid_Body();
};

