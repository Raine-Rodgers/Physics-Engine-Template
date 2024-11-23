#include "Rigid_Body_Rectangle.h"


Rigid_Body_Rectangle::Rigid_Body_Rectangle() : Rigid_Body()
{
	this->size = sf::Vector2f(100, 30);
	this->position = sf::Vector2f(500, 500);
	this->rectangle.setSize(this->size);
	this->rectangle.setPosition(this->position);
	this->rectangle.setFillColor(sf::Color::Red);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(bool lockedPosition, sf::Vector2f position, float rotation) : Rigid_Body(lockedPosition)
{
	this->size = sf::Vector2f(100, 30);
	this->position = position;
	this->rectangle.setSize(this->size);
	this->rectangle.setPosition(this->position);
	this->rectangle.setFillColor(sf::Color::Red);
	this->rectangle.setRotation(rotation);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f position, bool lockedPosition, float terminalVelocity)
: Rigid_Body(acceleration, velocity, mass, friction, lockedPosition, terminalVelocity)
{
	this->size = size;
	this->position = position;
	

	this->rectangle.setSize(this->size);
}

Rigid_Body_Rectangle::~Rigid_Body_Rectangle()
{
}

sf::Vector2f Rigid_Body_Rectangle::GetPosition()
{
	this->position = this->rectangle.getPosition();
	std::cout << this->rectangle.getPosition().y << std::endl;
	return this->position;
}

sf::Vector2f Rigid_Body_Rectangle::GetTransformedPoint(int index)
{
	return this->rectangle.getTransform().transformPoint(this->rectangle.getPoint(index));
}

void Rigid_Body_Rectangle::SetColor(sf::Color color)
{
	this->rectangle.setFillColor(color);
}

void Rigid_Body_Rectangle::ThrowThings()
{
}

void Rigid_Body_Rectangle::PhysicsUpdate(float gravity)
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
		this->position = this->rectangle.getPosition();
		std::cout << this->rectangle.getPosition().y << std::endl;
		this->rectangle.move(this->velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);

		return;
	}

	this->velocity.y = this->terminalVelocity;
	this->position = this->rectangle.getPosition();
	std::cout << this->rectangle.getPosition().y << std::endl;
	this->rectangle.move(this->velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);
	
}

void Rigid_Body_Rectangle::Update(float gravity)
{
	PhysicsUpdate(gravity);
}

void Rigid_Body_Rectangle::Render(sf::RenderWindow* window)
{
	window->draw(this->rectangle);
}
