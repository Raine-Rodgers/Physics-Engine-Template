#pragma once
#include "Rigid_Body.h"
#include "Engine_Tools.h"

class Rigid_Body_Rectangle : public Rigid_Body
{
private:
	//sf::RectangleShape				rectangle;
	sf::Vector2f					size;
	Engine_Tools					engineTools;
	
public:
	// Accessors and Modifiers
	
	//sf::RectangleShape				GetRectangle() { return this->rectangle; }
	sf::Vector2f					GetSize() { return this->size; }
	std::vector<sf::Vector2f>		GetVertices(int vertexCount);
	int								GetPointCount() { return this->rectangle.getPointCount(); }

	void							SetColor(sf::Color color);
	void							SetSize(sf::Vector2f size) { this->size = size; }
	void							SetRotation(float rotation) { this->rectangle.setRotation(rotation); }

	// Update Functions

	void							PhysicsUpdate(float gravity);
	void							Update(float gravity);
	void							Render(sf::RenderWindow* window);

	Rigid_Body_Rectangle();
	Rigid_Body_Rectangle(bool lockedPosition, bool collidable, sf::Vector2f position, float rotation, int shapeType);
	Rigid_Body_Rectangle(sf::Vector2f velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f position, bool lockedPosition, bool collidable, float terminalVelocity, int shapeType);
	~Rigid_Body_Rectangle();
};

