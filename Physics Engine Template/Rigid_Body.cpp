#include "Rigid_Body.h"

Rigid_Body::Rigid_Body()
{
	this->velocity = sf::Vector2f(0, 0);
	this->acceleration = sf::Vector2f(0, 0);
	this->mass = 1;
	this->friction = 0.1f;
	this->lockedPosition = false;
	this->terminalVelocity = 20.f;
}

Rigid_Body::Rigid_Body(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, bool lockedPosition, float terminalVelocity)
{
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->mass = mass;
	this->friction = friction;
	this->lockedPosition = lockedPosition;
	this->terminalVelocity = terminalVelocity;
}

Rigid_Body::~Rigid_Body()
{
}
