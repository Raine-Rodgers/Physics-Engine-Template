#include "Game_Engine.h"


Game_Engine::Game_Engine()
{
	this->initWindow();
	this->initVariables();
}

Game_Engine::~Game_Engine()
{
	delete this->window;
}


void Game_Engine::initWindow()
{
	// sf::VideoMode::getDesktopMode().width * 0.5f, sf::VideoMode::getDesktopMode().height * 0.7f
	this->videoMode = sf::VideoMode(900, 900);
	this->window = new sf::RenderWindow(this->videoMode, "Template", sf::Style::Close | sf::Style::Titlebar);

	this->window->setFramerateLimit(60);
}

void Game_Engine::initVariables()
{
	this->gravity = 0.2f;
	this->drag = 0.5f;
	this->shape = Rigid_Body_Rectangle();
	this->circle = Rigid_Body_Circle();
}

void Game_Engine::CollisionDetection()
{
}

void Game_Engine::PollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch(this->event.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if(this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

void Game_Engine::Update()
{
	this->PollEvents();
	this->circle.Update(this->gravity);
	this->CollisionDetection();
}

void Game_Engine::Render()
{
	this->window->clear();

	this->shape.Render(this->window);

	this->circle.Render(this->window);

	this->window->display();
}
