#pragma once
#include "Rigid_Body.h"
class Rigid_Body_Circle : public Rigid_Body
{
private:
	sf::CircleShape circle;
	float radius;
	sf::Vector2f position;

public:
	Rigid_Body_Circle();
	Rigid_Body_Circle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f position, bool lockedPosition);
	~Rigid_Body_Circle();

	void Update();
	void Render(sf::RenderWindow* window);
};

