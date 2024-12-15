#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Rigid_Body
{
protected:
	sf::Vector2f					velocity;
	sf::Vector2f					force;
	float							terminalVelocity;
	float							mass;
	float							friction;
	bool							lockedPosition;
	bool							collidable;
	int								shapeType;
	sf::Vector2f					position;

	sf::RectangleShape				rectangle;
	sf::CircleShape					circle;

public:

	// Accessors and Modifiers
	sf::Vector2f					GetVelocity()									{ return this->velocity; }
	sf::Vector2f					GetPosition()									{ return this->position; }
	float							GetTerminalVelocity()							{ return this->terminalVelocity; }
	float							GetMass()										{ return this->mass; }
	float							GetFriction()									{ return this->friction; }
	bool							GetLockedPosition()								{ return this->lockedPosition; }
	bool							GetCollidable()									{ return this->collidable; }

	void							SetVelocity(sf::Vector2f velocity)				{ this->velocity = velocity; }
	void							SetPosition(sf::Vector2f position)				{ this->position = position; }
	void							SetTerminalVelocity(float terminalVelocity)		{ this->terminalVelocity = terminalVelocity; }
	void							SetMass(float mass)								{ this->mass = mass; }
	void							SetFriction(float friction)						{ this->friction = friction; }
	void							SetLockedPosition(bool lockedPosition)			{ this->lockedPosition = lockedPosition; }
	void							SetCollidable(bool collidable)					{ this->collidable = collidable; }

	// Methods
	void							AddForce(sf::Vector2f force)					{ this->force += force; }

	// Constructors and Destructors
	Rigid_Body();
	Rigid_Body(bool lockedPosition, bool collidable, int shapeType);
	Rigid_Body(sf::Vector2f velocity,float mass, float friction, bool lockedPosition, float terminalVelocity, bool collidable, int shapeType);
	void CreateShape(int shapeType);
	~Rigid_Body();
};


