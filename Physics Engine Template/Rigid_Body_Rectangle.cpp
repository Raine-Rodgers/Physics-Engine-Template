#include "Rigid_Body_Rectangle.h"

// Constructors and Destructors
Rigid_Body_Rectangle::Rigid_Body_Rectangle() : Rigid_Body()
{
	this->size = sf::Vector2f(100, 30);
	this->position = sf::Vector2f(500, 500);
	this->rectangle.setSize(this->size);
	this->rectangle.setPosition(this->position);
	this->rectangle.setFillColor(sf::Color::Red);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(bool lockedPosition, bool collidable, sf::Vector2f position, float rotation) : Rigid_Body(lockedPosition, collidable)
{
	this->size = sf::Vector2f(100, 30);
	this->position = position;
	this->rectangle.setSize(this->size);
	this->rectangle.setPosition(this->position);
	this->rectangle.setFillColor(sf::Color::Red);
	this->rectangle.setRotation(rotation);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(sf::Vector2f velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f position, bool lockedPosition, bool collidable, float terminalVelocity)
: Rigid_Body(velocity, mass, friction, lockedPosition, terminalVelocity, collidable)
{
	this->size = size;
	this->position = position;
	

	this->rectangle.setSize(this->size);
}

Rigid_Body_Rectangle::~Rigid_Body_Rectangle()
{
}

// Accessors and Modifiers
sf::Vector2f Rigid_Body_Rectangle::GetPosition()
{
	this->position = this->rectangle.getPosition();
	return this->position;
}

std::vector<sf::Vector2f> Rigid_Body_Rectangle::GetVertices(int vertexCount)
{
	std::vector<sf::Vector2f> vertices;
	for (int i = 0; i < vertexCount; i++)
	{
		vertices.push_back (this->rectangle.getTransform().transformPoint(this->rectangle.getPoint(i)));
	}
	return vertices;
}

void Rigid_Body_Rectangle::SetColor(sf::Color color)
{
	this->rectangle.setFillColor(color);
}

// Update Functions
void Rigid_Body_Rectangle::PhysicsUpdate(float gravity)
{
	engineTools.deltaTime = engineTools.clock.restart();
	if (lockedPosition)
	{
		return;
	}

	if (velocity.y < terminalVelocity) // apparently removing this-> fixes the issue where the velocity is not set to 0 when using a low gravity value. No clue why tbh
	{
		velocity.y += gravity;
		position = rectangle.getPosition();
		velocity += force * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier;
		rectangle.move(velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);

		return;
	}

	velocity.y = terminalVelocity;
	position = rectangle.getPosition();
	rectangle.move(velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);
	
}

void Rigid_Body_Rectangle::Update(float gravity)
{
	PhysicsUpdate(gravity);
}

void Rigid_Body_Rectangle::Render(sf::RenderWindow* window)
{
	window->draw(this->rectangle);
}
