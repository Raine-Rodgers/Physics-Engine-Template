#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Engine_Tools.h"

class Rigid_Body
{
protected:
	Engine_Tools					_engineTools;
	sf::Vector2f					_position;
	sf::Vector2f					_acceleration;
	float							_terminalVelocity;
	bool							_lockedPosition;
	bool							_collidable;
	int								_shapeType;

	sf::RectangleShape				_rectangle;
	sf::CircleShape					_circle;

public:
	sf::Vector2f					_velocity;
	sf::Vector2f					_force;
	float							_mass;
	float							_friction;
	float							_restitution;

	// Accessors and Modifiers
	sf::Vector2f					GetVelocity()									{ return _velocity; }
	sf::Vector2f					GetPosition()									{ return _position; }
	float							GetTerminalVelocity()							{ return _terminalVelocity; }
	float							GetMass()										{ return _mass; }
	float							GetFriction()									{ return _friction; }
	float							GetRestitution()								{ return _restitution; }
	bool							GetLockedPosition()								{ return _lockedPosition; }
	bool							GetCollidable()									{ return _collidable; }
	int								GetShapeType()									{ return _shapeType; }


	sf::CircleShape					GetCircle()										{ return _circle; }
	float							GetRadius()										{ return _circle.getRadius(); }
	void							SetRadius(float radius)							{ _circle.setRadius(radius); }
	void							SetOrigin() { _circle.setOrigin(_circle.getRadius(), _circle.getRadius()); }

	sf::RectangleShape				GetRectangle()									{ return _rectangle; }
	int								GetPointCount()									{ return _rectangle.getPointCount(); }
	std::vector<sf::Vector2f>		GetVertices(int vertexCount);
	float							GetRotation()									{ return _rectangle.getRotation(); }
	sf::Vector2f					GetSize()										{ return _rectangle.getSize(); }
	void							SetRotation(float rotation)						{ _rectangle.setRotation(rotation); }
	void							SetSize(sf::Vector2f size)						{ _rectangle.setSize(size); }

	void							SetVelocity(sf::Vector2f velocity)				{ _velocity = velocity; }
	void							SetPosition(sf::Vector2f position);
	void							SetTerminalVelocity(float terminalVelocity)		{ _terminalVelocity = terminalVelocity; }
	void							SetMass(float mass)								{ _mass = mass; }
	void							SetFriction(float friction)						{ _friction = friction; }
	void							SetRestitution(float restitution)				{ _restitution = restitution; }
	void							SetLockedPosition(bool lockedPosition)			{ _lockedPosition = lockedPosition; }
	void							SetCollidable(bool collidable)					{ _collidable = collidable; }
	void							SetColor(sf::Color color);

	// Methods
	void							AddForce(sf::Vector2f force)					{ _force += force; }
	void							Update(float gravity);
	void							RectPhysicsUpdate(float gravity);
	void							CircPhysicsUpdate(float gravity);
	void							Render(sf::RenderWindow* window);

	// Constructors and Destructors
	Rigid_Body();
	Rigid_Body(bool lockedPosition, bool collidable, int shapeType);
	Rigid_Body(sf::Vector2f velocity,float mass, float friction, bool lockedPosition, float terminalVelocity, bool collidable, int shapeType, float restitution);
	~Rigid_Body();
};


