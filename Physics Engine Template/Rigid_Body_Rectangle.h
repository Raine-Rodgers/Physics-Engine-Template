#pragma once
#include "Rigid_Body.h"

class Rigid_Body_Rectangle : public Rigid_Body
{
private:
	sf::RectangleShape rectangle;
	sf::Vector2f size;
	sf::Vector2f position;
	
public:
	Rigid_Body_Rectangle();
	Rigid_Body_Rectangle(sf::Vector2f acceleration, sf::Vector2f velocity, float mass, float friction, sf::Vector2f size, sf::Vector2f position, bool lockedPosition, float terminalVelocity);
	~Rigid_Body_Rectangle();

	sf::RectangleShape GetRectangle() { return this->rectangle; }
	void Update();
	void Render(sf::RenderWindow* window);
};

