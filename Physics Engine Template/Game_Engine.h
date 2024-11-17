#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Rigid_Body_Rectangle.h"
#include "Rigid_Body_Circle.h"
#include "Engine_Tools.h"

class Game_Engine
{
private:
	void initWindow();
	void initVariables();

	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event event;
	Engine_Tools engineTools;

	// test variables
	Rigid_Body_Rectangle* rectangleA;
	Rigid_Body_Rectangle* rectangleB;
	//

	float gravity;
	float drag;

public:
	Game_Engine();
	~Game_Engine();

	const bool running() const { return this->window->isOpen(); }
	void PollEvents();
	void PhysicsUpdate();
	void Update();
	void Render();
};

