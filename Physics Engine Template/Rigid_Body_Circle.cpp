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

Rigid_Body_Circle::Rigid_Body_Circle(sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f, bool lockedPosition, bool collidable, float terminalVelocity)
: Rigid_Body(velocity, mass, friction, lockedPosition, terminalVelocity, collidable)
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
	if (lockedPosition)
	{
		return;
	}

	if (velocity.y < terminalVelocity)
	{
		velocity.y += gravity;
		position = circle.getPosition();
		velocity += force * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier;
		circle.move(velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);
		force = sf::Vector2f(0, 0);
		return;
	}

	velocity.y = terminalVelocity;
	position = circle.getPosition();
	circle.move(velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);
}


void Rigid_Body_Circle::Update(float gravity)
{
	this->PhysicsUpdate(gravity);
}

void Rigid_Body_Circle::Render(sf::RenderWindow* window)
{
	window->draw(this->circle);
}


