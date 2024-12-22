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
	std::vector<Rigid_Body*> objectList;

	// test variables
	Rigid_Body*	rectangleA;
	Rigid_Body*	rectangleB;


public:
	const bool				running() const { return this->window->isOpen(); } // returns if the window is open or not
	void					PollEvents();
	void					Movement();
	void					PhysicsUpdate();
	void					CollisionCheck();
	void					CollisionResolve(int indexShapeA, int indexShapeB, sf::Vector2f normal, float depth);
	void					Update();
	void					Render();

	Game_Engine();
	~Game_Engine();
};

