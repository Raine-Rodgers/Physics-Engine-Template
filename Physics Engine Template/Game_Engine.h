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
	void					initWindow();
	void					initVariables();

	sf::VideoMode			videoMode;
	sf::RenderWindow*		window;
	sf::Event				event;
	Engine_Tools			engineTools;
	float					gravity;
	float					drag;

	// test variables
	Rigid_Body_Rectangle*	rectangleA;
	Rigid_Body_Rectangle*	rectangleB;


public:
	const bool				running() const { return this->window->isOpen(); } // returns if the window is open or not
	void					PollEvents();
	void					Movement();
	void					PhysicsUpdate();
	void					CollisionUpdate();
	void					Update();
	void					Render();

	Game_Engine();
	~Game_Engine();
};

