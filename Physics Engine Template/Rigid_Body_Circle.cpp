#include "Rigid_Body_Circle.h"

Rigid_Body_Circle::Rigid_Body_Circle()
: Rigid_Body()
{
	this->engineTools = Engine_Tools();
	this->radius = 20;
	this->position = sf::Vector2f(450, 450);

	this->circle = sf::CircleShape(this->radius);
	this->circle.setPosition(this->position);
}

Rigid_Body_Circle::Rigid_Body_Circle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, float radius, sf::Vector2f, bool lockedPosition)
: Rigid_Body(acceleration, velocity, mass, friction, lockedPosition)
{
	this->radius = radius;
	this->position = position;


	this->circle.setRadius(this->radius);
	this->circle.setPosition(this->position);
}

Rigid_Body_Circle::~Rigid_Body_Circle()
{
}

// TODO: create gravity update function
void Rigid_Body_Circle::PhysicsUpdate(float gravity)
{
	engineTools.deltaTime = engineTools.clock.restart();
	if (!this->lockedPosition)
	{
		this->velocity.y += gravity;
		this->velocity += this->acceleration;
		this->position = this->circle.getPosition();
		std::cout << engineTools.deltaTime.asSeconds() << std::endl;
		this->circle.setPosition(this->position.x, this->position.y += this->velocity.y * engineTools.deltaTime.asSeconds() * 30);
	}
}

void Rigid_Body_Circle::Update(float gravity)
{
	this->PhysicsUpdate(gravity);
}

void Rigid_Body_Circle::Render(sf::RenderWindow* window)
{
	window->draw(this->circle);
}
