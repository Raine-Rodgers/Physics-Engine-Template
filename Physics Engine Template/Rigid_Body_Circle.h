#pragma once
#include "Rigid_Body.h"
#include "Engine_Tools.h"
#include <iostream>

class Rigid_Body_Circle : public Rigid_Body
{
private:
	sf::CircleShape		circle;
	float				radius;
	sf::Vector2f		position;
	Engine_Tools		engineTools;

public:
	Rigid_Body_Circle();
	Rigid_Body_Circle(bool lockedPosition, bool collidable);
	Rigid_Body_Circle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f position, bool lockedPosition, bool collidable, float terminalVelocity);
	~Rigid_Body_Circle();

	// Accessors and Modifiers
	sf::CircleShape		GetCircle() { return this->circle; }
	float				GetRadius() { return this->radius; }
	sf::Vector2f		GetPosition() { return this->position; }

	void				SetColor(sf::Color color);
	void				SetRadius(float radius) { this->radius = radius; }
	void				SetPosition(sf::Vector2f position) { this->position = position; }


	// update and render functions
	void PhysicsUpdate(float gravity);
	void Update(float gravity);
	void Render(sf::RenderWindow* window);
};

