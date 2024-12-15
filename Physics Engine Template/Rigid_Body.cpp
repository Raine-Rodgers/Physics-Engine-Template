#include "Rigid_Body.h"

Rigid_Body::Rigid_Body()
{
	this->velocity = sf::Vector2f(0, 0);
	this->mass = 1;
	this->friction = 0.1f;
	this->lockedPosition = false;
	this->collidable = true;
	this->terminalVelocity = 20.f;
	this->force = sf::Vector2f(0, 0);
	this->shapeType = 0;
	CreateShape(this->shapeType);
}

Rigid_Body::Rigid_Body(bool lockedPosition, bool collidable, int shapeType)
{
	this->velocity = sf::Vector2f(0, 0);
	this->mass = 1;
	this->friction = 0.1f;
	this->lockedPosition = lockedPosition;
	this->collidable = collidable;
	this->terminalVelocity = 20.f; // havent done anything yet with this
	this->force = sf::Vector2f(0, 0);
	this->shapeType = shapeType;
	CreateShape(this->shapeType);
}

Rigid_Body::Rigid_Body(sf::Vector2f velocity, float mass, float friction, bool lockedPosition, float terminalVelocity, bool collidable, int shapeType)
{
	this->velocity = velocity;
	this->mass = mass;
	this->friction = friction;
	this->lockedPosition = lockedPosition;
	this->collidable = collidable;
	this->terminalVelocity = terminalVelocity;
	this->force = sf::Vector2f(0, 0);
	this->shapeType = shapeType;
	CreateShape(this->shapeType);
}

void Rigid_Body::CreateShape(int shapeType)
{
	switch (shapeType)
	{
	case 0:
		break;
	case 1:
		break;
	default:
		break;
	}
}

Rigid_Body::~Rigid_Body()
{
}
