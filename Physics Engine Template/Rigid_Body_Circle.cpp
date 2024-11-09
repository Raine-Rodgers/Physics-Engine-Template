#include "Rigid_Body_Circle.h"

Rigid_Body_Circle::Rigid_Body_Circle()
: Rigid_Body()
{
	this->radius = 20;
	this->position = sf::Vector2f(450, 450);

	this->circle.setRadius(this->radius);
	this->circle.setPosition(this->position);
}

Rigid_Body_Circle::Rigid_Body_Circle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f, bool lockedPosition)
: Rigid_Body(acceleration, velocity, mass, friction, lockedPosition)
{
	this->radius = radius;
	this->position = position;


	this->circle.setRadius(this->radius);
	this->circle.setPosition(this->position);
}

Rigid_Body_Circle::~Rigid_Body_Circle()
{
}

// TODO: create gravity update function
void Rigid_Body_Circle::PhysicsUpdate(float gravity)
{
	if (!this->lockedPosition)
	{
		this->velocity.y += gravity;
	}
	this->velocity += this->acceleration;
}

void Rigid_Body_Circle::Update(float gravity)
{
	this->PhysicsUpdate(gravity);
}

void Rigid_Body_Circle::Render(sf::RenderWindow* window)
{
	window->draw(this->circle);
}
