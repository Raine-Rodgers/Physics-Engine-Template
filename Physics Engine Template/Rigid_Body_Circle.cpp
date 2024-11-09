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

void Rigid_Body_Circle::Update()
{
}

void Rigid_Body_Circle::Render(sf::RenderWindow* window)
{
	window->draw(this->circle);
}
