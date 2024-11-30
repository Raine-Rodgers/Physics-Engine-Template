#include "Rigid_Body_Circle.h"

Rigid_Body_Circle::Rigid_Body_Circle()
: Rigid_Body()
{
	this->engineTools = Engine_Tools();
	this->radius = 20;
	this->position = sf::Vector2f(550, 450);

	this->circle = sf::CircleShape(this->radius);
	this->circle.setPosition(this->position);

}

Rigid_Body_Circle::Rigid_Body_Circle(bool lockedPosition, bool collidable)
	: Rigid_Body(lockedPosition, collidable)
{
	this->engineTools = Engine_Tools();
	this->radius = 20;
	this->position = sf::Vector2f(550, 450);

	this->circle = sf::CircleShape(this->radius);
	this->circle.setPosition(this->position);
}

Rigid_Body_Circle::Rigid_Body_Circle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f, bool lockedPosition, bool collidable, float terminalVelocity)
: Rigid_Body(acceleration, velocity, mass, friction, lockedPosition, terminalVelocity, collidable)
{
	this->radius = radius;
	this->position = position;


	this->circle.setRadius(this->radius);
	this->circle.setPosition(this->position);
}

Rigid_Body_Circle::~Rigid_Body_Circle()
{
}

void Rigid_Body_Circle::PhysicsUpdate(float gravity)
{
	engineTools.deltaTime = engineTools.clock.restart();
	if (this->lockedPosition)
	{
		return;
	}

	if (this->velocity.y < this->terminalVelocity)
	{
		this->velocity.y += gravity;
		this->velocity += this->acceleration;
		this->position = this->circle.getPosition();
		this->circle.move(this->velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);
		//this->circle.setPosition(this->position.x, this->position.y += this->velocity.y * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);
		return;
	}

	this->velocity.y = this->terminalVelocity;
	this->position = this->circle.getPosition();
	this->circle.move(this->velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);
}

// Accessors and Modifiers
void Rigid_Body_Circle::SetColor(sf::Color color)
{
	this->circle.setFillColor(color);
}


void Rigid_Body_Circle::Update(float gravity)
{
	this->PhysicsUpdate(gravity);
}

void Rigid_Body_Circle::Render(sf::RenderWindow* window)
{
	window->draw(this->circle);
}


