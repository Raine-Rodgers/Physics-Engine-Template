#include "Rigid_Body_Rectangle.h"

// Constructors and Destructors
Rigid_Body_Rectangle::Rigid_Body_Rectangle() : Rigid_Body()
{
	this->size = sf::Vector2f(100, 30);
	this->_position = sf::Vector2f(500, 500);
	_rectangle.setSize(this->size);
	_rectangle.setPosition(this->_position);
	_rectangle.setFillColor(sf::Color::Red);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(bool _lockedPosition, bool collidable, sf::Vector2f _position, float rotation, int shapeType) : Rigid_Body(_lockedPosition, collidable, shapeType)
{
	this->size = sf::Vector2f(100, 30);
	this->_position = _position;
	_rectangle.setSize(this->size);
	_rectangle.setPosition(this->_position);
	_rectangle.setFillColor(sf::Color::Red);
	_rectangle.setRotation(rotation);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(sf::Vector2f _velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f _position, bool _lockedPosition, bool collidable, float _terminalVelocity, int shapeType)
: Rigid_Body(_velocity, mass, friction, _lockedPosition, _terminalVelocity, collidable, shapeType)
{
	this->size = size;
	this->_position = _position;
	

	_rectangle.setSize(this->size);
}

Rigid_Body_Rectangle::~Rigid_Body_Rectangle()
{
}

// Accessors and Modifiers

void Rigid_Body_Rectangle::SetColor(sf::Color color)
{
	_rectangle.setFillColor(color);
}

