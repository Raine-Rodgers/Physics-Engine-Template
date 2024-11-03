#include "Rigid_Body_Rectangle.h"


Rigid_Body_Rectangle::Rigid_Body_Rectangle() : Rigid_Body()
{
	this->size = sf::Vector2f(20, 20);
	this->position = sf::Vector2f(100, 100);
	this->rectangle.setSize(this->size);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f position)
: Rigid_Body(acceleration, velocity, mass, friction)
{
	this->size = size;
	this->position = position;
	

	this->rectangle.setSize(this->size);
}

Rigid_Body_Rectangle::~Rigid_Body_Rectangle()
{
}
