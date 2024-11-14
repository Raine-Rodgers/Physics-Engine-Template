#include "Map1.h"

Map1::Map1()
{
	this->wall1 = sf::RectangleShape(sf::Vector2f(20, 300));
	this->wall1.setPosition(100, 100);

	this->wall2 = sf::RectangleShape(sf::Vector2f(300, 20));
	this->wall2.setPosition(100, 100);

	this->wall3 = sf::RectangleShape(sf::Vector2f(20, 300));
	this->wall3.setPosition(400, 100);

	this->wall4 = sf::RectangleShape(sf::Vector2f(300, 20));
	this->wall4.setPosition(100, 400);
}

Map1::~Map1()
{
}

void Map1::Update()
{
}

void Map1::Render(sf::RenderWindow* window)
{
	window->draw(this->wall1);
	window->draw(this->wall2);
	window->draw(this->wall3);
	window->draw(this->wall4);
}
