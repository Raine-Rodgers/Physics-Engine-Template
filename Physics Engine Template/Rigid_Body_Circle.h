#pragma once
#include "Rigid_Body.h"
#include "Engine_Tools.h"
#include <iostream>

class Rigid_Body_Circle : public Rigid_Body
{
private:
	sf::CircleShape		circle;
	float				radius;
	Engine_Tools		engineTools;

public:
	// Accessors and Modifiers
	sf::CircleShape		GetCircle()							{ return this->circle; }
	float				GetRadius()							{ return this->radius; }
	sf::Vector2f		GetPosition()						{ return this->position; }

	void				SetRadius(float radius)				{ this->radius = radius; }
	void				SetColor(sf::Color color)			{ this->circle.setFillColor(color); }


	// update and render functions
	void				PhysicsUpdate(float gravity);
	void				Update(float gravity);
	void				Render(sf::RenderWindow* window);

	// Constructors and Destructors
	Rigid_Body_Circle();
	Rigid_Body_Circle(bool lockedPosition, bool collidable, int shapeType);
	Rigid_Body_Circle(sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f position, bool lockedPosition, bool collidable, float terminalVelocity, int shapeType);
	~Rigid_Body_Circle();
};