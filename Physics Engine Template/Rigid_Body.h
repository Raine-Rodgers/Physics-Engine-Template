#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Rigid_Body
{
protected:
	sf::Vector2f	velocity;
	sf::Vector2f	acceleration;
	float			terminalVelocity;
	float			mass;
	float			friction;
	bool			lockedPosition;
	bool			collidable;

public:

	// Accessors and Modifiers
	sf::Vector2f	GetVelocity()									{ return this->velocity; }
	sf::Vector2f	GetAcceleration()								{ return this->acceleration; }
	float			GetTerminalVelocity()							{ return this->terminalVelocity; }
	float			GetMass()										{ return this->mass; }
	float			GetFriction()									{ return this->friction; }
	bool			GetLockedPosition()								{ return this->lockedPosition; }
	bool			GetCollidable()									{ return this->collidable; }

	void			SetVelocity(sf::Vector2f velocity)				{ this->velocity = velocity; }
	void			SetAcceleration(sf::Vector2f acceleration)		{ this->acceleration = acceleration; }
	void			SetTerminalVelocity(float terminalVelocity)		{ this->terminalVelocity = terminalVelocity; }
	void			SetMass(float mass)								{ this->mass = mass; }
	void			SetFriction(float friction)						{ this->friction = friction; }
	void			SetLockedPosition(bool lockedPosition)			{ this->lockedPosition = lockedPosition; }
	void			SetCollidable(bool collidable)					{ this->collidable = collidable; }

	// Constructors and Destructors
	Rigid_Body();
	Rigid_Body(bool lockedPosition, bool collidable);
	Rigid_Body(sf::Vector2f acceleration, sf::Vector2f velocity,float mass, float friction, bool lockedPosition, float terminalVelocity, bool collidable);
	~Rigid_Body();
};


