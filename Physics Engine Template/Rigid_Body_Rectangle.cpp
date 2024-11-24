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
		//std::cout << vertices[i].x << " " << vertices[i].y << std::endl;
	}
	return vertices;
}

void Rigid_Body_Rectangle::SetColor(sf::Color color)
{
	this->rectangle.setFillColor(color);
}

void Rigid_Body_Rectangle::ThrowThings()
{
	std::cout << sf::Vector2f(0, this->rectangle.getTransform().transformPoint(this->rectangle.getPoint(2)).y).y << std::endl;
}

// Update Functions
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
		this->rectangle.move(this->velocity * engineTools.deltaTime.asSeconds() * engineTools.dtMultiplier);

		return;
	}

	this->velocity.y = this->terminalVelocity;
	this->position = this->rectangle.getPosition();
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
