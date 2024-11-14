#pragma once
#include "Rigid_Body.h"
#include "Engine_Tools.h"
#include <iostream>

class Rigid_Body_Circle : public Rigid_Body
{
private:
	sf::CircleShape circle;
	float radius;
	sf::Vector2f position;
	Engine_Tools engineTools;

public:
	Rigid_Body_Circle();
	Rigid_Body_Circle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f position, bool lockedPosition, float terminalVelocity);
	~Rigid_Body_Circle();

	sf::CircleShape GetCircle() { return this->circle; }
	void PhysicsUpdate(float gravity);
	void Update(float gravity);
	void Render(sf::RenderWindow* window);
};

