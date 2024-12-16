#include "Rigid_Body_Circle.h"

Rigid_Body_Circle::Rigid_Body_Circle()
: Rigid_Body()
{
	this->engineTools = Engine_Tools();
	this->radius = 20;
	this->_position = sf::Vector2f(550, 450);

	this->_circle = sf::CircleShape(this->radius);
	this->_circle.setPosition(this->_position);

}

Rigid_Body_Circle::Rigid_Body_Circle(bool _lockedPosition, bool collidable, int shapeType)
	: Rigid_Body(_lockedPosition, collidable, shapeType)
{
	this->engineTools = Engine_Tools();
	this->radius = 20;
	this->_position = sf::Vector2f(550, 450);

	this->_circle = sf::CircleShape(this->radius);
	this->_circle.setPosition(this->_position);
}

Rigid_Body_Circle::Rigid_Body_Circle(sf::Vector2f _velocity, float mass, float friction, float radius, sf::Vector2f, bool _lockedPosition, bool collidable, float _terminalVelocity, int shapeType)
: Rigid_Body(_velocity, mass, friction, _lockedPosition, _terminalVelocity, collidable, shapeType)
{
	this->radius = radius;
	this->_position = _position;


	_circle.setRadius(this->radius);
	_circle.setPosition(this->_position);
}

Rigid_Body_Circle::~Rigid_Body_Circle()
{
}


