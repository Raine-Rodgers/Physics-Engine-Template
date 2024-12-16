#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Engine_Tools.h"

class Rigid_Body
{
protected:
	Engine_Tools					_engineTools;
	sf::Vector2f					_velocity;
	sf::Vector2f					_force;
	sf::Vector2f					_position;
	float							_terminalVelocity;
	float							_mass;
	float							_friction;
	bool							_lockedPosition;
	bool							_collidable;
	int								_shapeType;

	sf::RectangleShape				_rectangle;
	sf::CircleShape					_circle;

public:

	// Accessors and Modifiers
	sf::Vector2f					GetVelocity()									{ return this->_velocity; }
	sf::Vector2f					GetPosition()									{ return this->_position; }
	float							GetTerminalVelocity()							{ return this->_terminalVelocity; }
	float							GetMass()										{ return this->_mass; }
	float							GetFriction()									{ return this->_friction; }
	bool							GetLockedPosition()								{ return this->_lockedPosition; }
	bool							GetCollidable()									{ return this->_collidable; }

	sf::CircleShape					GetCircle()										{ return this->_circle; }
	float							GetRadius()										{ return this->_circle.getRadius(); }

	sf::RectangleShape				GetRectangle()									{ return this->_rectangle; }
	int								GetShapeType()									{ return this->_shapeType; }
	int								GetPointCount()									{ return this->_rectangle.getPointCount(); }
	std::vector<sf::Vector2f>		GetVertices(int vertexCount);

	void							SetVelocity(sf::Vector2f velocity)				{ this->_velocity = velocity; }
	void							SetPosition(sf::Vector2f position)				{ this->_position = position; }
	void							SetTerminalVelocity(float terminalVelocity)		{ this->_terminalVelocity = terminalVelocity; }
	void							SetMass(float mass)								{ this->_mass = mass; }
	void							SetFriction(float friction)						{ this->_friction = friction; }
	void							SetLockedPosition(bool lockedPosition)			{ this->_lockedPosition = lockedPosition; }
	void							SetCollidable(bool collidable)					{ this->_collidable = collidable; }

	// Methods
	void							AddForce(sf::Vector2f force)					{ this->_force += force; }
	void							Update(float gravity, int shapeType);
	void							RectPhysicsUpdate(float gravity);
	void							CircPhysicsUpdate(float gravity);
	void							Render(sf::RenderWindow* window);

	// Constructors and Destructors
	Rigid_Body();
	Rigid_Body(bool lockedPosition, bool collidable, int shapeType);
	Rigid_Body(sf::Vector2f velocity,float mass, float friction, bool lockedPosition, float terminalVelocity, bool collidable, int shapeType);
	~Rigid_Body();
};


