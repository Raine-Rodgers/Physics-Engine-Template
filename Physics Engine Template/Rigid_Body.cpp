#include "Rigid_Body.h"


Rigid_Body::Rigid_Body()
{
	this->_velocity = sf::Vector2f(0, 0);
	this->_mass = 1;
	this->_friction = 0.1f;
	this->_lockedPosition = false;
	this->_collidable = true;
	this->_terminalVelocity = 20.f;
	this->_force = sf::Vector2f(0, 0);
	this->_shapeType = 0;
	this->_restitution = 0.5f;
}

Rigid_Body::Rigid_Body(bool lockedPosition, bool collidable, int shapeType)
{
	this->_velocity = sf::Vector2f(0, 0);
	this->_mass = 1;
	this->_friction = 0.1f;
	this->_lockedPosition = lockedPosition;
	this->_collidable = collidable;
	this->_terminalVelocity = 20.f; // havent done anything yet with this
	this->_force = sf::Vector2f(0, 0);
	this->_shapeType = shapeType;
	this->_restitution = 0.5f;
}

Rigid_Body::Rigid_Body(sf::Vector2f velocity, float mass, float friction, bool lockedPosition, float terminalVelocity, bool collidable, int shapeType, float restitution)
{
	this->_velocity = velocity;
	this->_mass = mass;
	this->_friction = friction;
	this->_lockedPosition = lockedPosition;
	this->_collidable = collidable;
	this->_terminalVelocity = terminalVelocity;
	this->_force = sf::Vector2f(0, 0);
	this->_shapeType = shapeType;
	this->_restitution = restitution;
}

Rigid_Body::~Rigid_Body()
{
}

std::vector<sf::Vector2f> Rigid_Body::GetVertices(int vertexCount)
{
	std::vector<sf::Vector2f> vertices;
	for (int i = 0; i < vertexCount; i++)
	{
		vertices.push_back(_rectangle.getTransform().transformPoint(_rectangle.getPoint(i)));
	}
	return vertices;
}


void Rigid_Body::RectPhysicsUpdate(float gravity)
{
	_engineTools._deltaTime = _engineTools._clock.restart();
	if (_lockedPosition)
	{
		return;
	}

	if (_velocity.y < _terminalVelocity) // apparently removing this-> fixes the issue where the _velocity is not set to 0 when using a low gravity value. No clue why tbh
	{
		_velocity.y += gravity;
		_position = _rectangle.getPosition();
		_velocity += _force * _engineTools.DetlaTime();
		_rectangle.move(_velocity * _engineTools.DetlaTime());
		_force = { 0, 0 };
		return;
	}

	_velocity.y = _terminalVelocity;
	_position = _rectangle.getPosition();
	_rectangle.move(_velocity * _engineTools.DetlaTime());
}

void Rigid_Body::CircPhysicsUpdate(float gravity)
{
	_engineTools._deltaTime = _engineTools._clock.restart();
	if (_lockedPosition)
	{
		return;
	}

	if (_velocity.y < _terminalVelocity) // apparently removing this-> fixes the issue where the _velocity is not set to 0 when using a low gravity value. No clue why tbh
	{
		_velocity.y += gravity;
		_position = _circle.getPosition();
		_velocity += _force * _engineTools.DetlaTime();
		_circle.move(_velocity * _engineTools.DetlaTime());
		_force = { 0, 0 };
		return;
	}

	_velocity.y = _terminalVelocity;
	_position = _circle.getPosition();
	_circle.move(_velocity * _engineTools.DetlaTime());
}

void Rigid_Body::SetPosition(sf::Vector2f position)
{
	_position = position;
	switch (_shapeType)
	{
	case 0:
		_rectangle.setPosition(_position);
		break;
	case 1:
		_circle.setPosition(_position);
		break;
	default:
		throw std::invalid_argument("couldnt set position");
	}
}

void Rigid_Body::SetColor(sf::Color color)
{
	switch (_shapeType)
	{
	case 0:
		_rectangle.setFillColor(color);
		break;
	case 1:
		_circle.setFillColor(color);
		break;
	default:
		throw std::invalid_argument("couldnt change color");
	}
}

void Rigid_Body::Update(float gravity)
{

	switch (_shapeType)
	{
	case 0:
		RectPhysicsUpdate(gravity);
		break;
	case 1:
		CircPhysicsUpdate(gravity);
		break;
	default:
		throw std::invalid_argument("couldnt update");
	}
}

void Rigid_Body::Render(sf::RenderWindow* window)
{
	switch (_shapeType)
	{
	case 0:
		window->draw(_rectangle);
		break;
	case 1:
		window->draw(_circle);
		break;
	default:
		throw std::invalid_argument("couldnt render");
	}
}

