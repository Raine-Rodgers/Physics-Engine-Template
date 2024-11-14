#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Rigid_Body_Rectangle.h"
#include "Rigid_Body_Circle.h"
#include "Map1.h"

class Game_Engine
{
private:
	void initWindow();
	void initVariables();

	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event event;
	Rigid_Body_Rectangle shape;
	Rigid_Body_Circle circle;
	Map1 map1;

	float gravity;
	float drag;

public:
	Game_Engine();
	~Game_Engine();

	const bool running() const { return this->window->isOpen(); }
	void CollisionDetection();
	void PollEvents();
	void Update();
	void Render();
};

