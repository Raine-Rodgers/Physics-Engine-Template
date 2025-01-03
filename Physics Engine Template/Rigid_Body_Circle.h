#pragma once
#include "Rigid_Body.h"
#include "Engine_Tools.h"
#include <iostream>

class Rigid_Body_Circle : public Rigid_Body
{
private:
	float				radius;
	Engine_Tools		engineTools;

public:
	// Accessors and Modifiers
	float				GetRadius()							{ return this->radius; }

	void				SetRadius(float radius)				{ this->radius = radius; }


	// Constructors and Destructors
	Rigid_Body_Circle();
	Rigid_Body_Circle(bool lockedPosition, bool collidable, int shapeType);
	Rigid_Body_Circle(sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f position, bool lockedPosition, bool collidable, float terminalVelocity, int shapeType);
	~Rigid_Body_Circle();
};