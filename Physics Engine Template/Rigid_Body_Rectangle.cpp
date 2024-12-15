#include "Rigid_Body_Rectangle.h"

// Constructors and Destructors
Rigid_Body_Rectangle::Rigid_Body_Rectangle() : Rigid_Body()
{
	this->size = sf::Vector2f(100, 30);
	this->position = sf::Vector2f(500, 500);
	rectangle.setSize(this->size);
	rectangle.setPosition(this->position);
	rectangle.setFillColor(sf::Color::Red);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(bool lockedPosition, bool collidable, sf::Vector2f position, float rotation, int shapeType) : Rigid_Body(lockedPosition, collidable, shapeType)
{
	this->size = sf::Vector2f(100, 30);
	this->position = position;
	rectangle.setSize(this->size);
	rectangle.setPosition(this->position);
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setRotation(rotation);
}

Rigid_Body_Rectangle::Rigid_Body_Rectangle(sf::Vector2f velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f position, bool lockedPosition, bool collidable, float terminalVelocity, int shapeType)
: Rigid_Body(velocity, mass, friction, lockedPosition, terminalVelocity, collidable, shapeType)
{
	this->size = size;
	this->position = position;
	

	rectangle.setSize(this->size);
}

Rigid_Body_Rectangle::~Rigid_Body_Rectangle()
{
}

// Accessors and Modifiers

std::vector<sf::Vector2f> Rigid_Body_Rectangle::GetVertices(int vertexCount)
{
	std::vector<sf::Vector2f> vertices;
	for (int i = 0; i < vertexCount; i++)
	{
		vertices.push_back (rectangle.getTransform().transformPoint(rectangle.getPoint(i)));
	}
	return vertices;
}

void Rigid_Body_Rectangle::SetColor(sf::Color color)
{
	rectangle.setFillColor(color);
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
		force = sf::Vector2f(0, 0);
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
	window->draw(rectangle);
}
