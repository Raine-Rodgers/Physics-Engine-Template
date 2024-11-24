#pragma once
#include "Rigid_Body.h"
#include "Engine_Tools.h"

class Rigid_Body_Rectangle : public Rigid_Body
{
private:
	sf::RectangleShape rectangle;
	sf::Vector2f size;
	sf::Vector2f position;
	Engine_Tools engineTools;
	
public:
	Rigid_Body_Rectangle();
	Rigid_Body_Rectangle(bool lockedPosition, sf::Vector2f position, float rotation);
	Rigid_Body_Rectangle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f position, bool lockedPosition, float terminalVelocity);
	~Rigid_Body_Rectangle();

	// Accessors and Modifiers
	
	sf::RectangleShape				GetRectangle() { return this->rectangle; }
	sf::Vector2f					GetSize() { return this->size; }
	sf::Vector2f					GetPosition();
	std::vector<sf::Vector2f>		GetVertices(int vertexCount);
	int								GetPointCount() { return this->rectangle.getPointCount(); }

	void							SetColor(sf::Color color);
	void							SetSize(sf::Vector2f size) { this->size = size; }
	void							SetPosition(sf::Vector2f position) { this->position = position; }
	
	// no use function purely for testing
	void ThrowThings();

	// Update Functions

	void PhysicsUpdate(float gravity);
	void Update(float gravity);
	void Render(sf::RenderWindow* window);
};

