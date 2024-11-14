#pragma once

#include <SFML/Graphics.hpp>

class Map1
{
private:
	sf::RectangleShape wall1;
	sf::RectangleShape wall2;
	sf::RectangleShape wall3;
	sf::RectangleShape wall4;
public:
	Map1();
	~Map1();

	void Update();
	void Render(sf::RenderWindow* window);
};

