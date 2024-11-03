#include "Game_Engine.h"


Game_Engine::Game_Engine()
{
	this->initWindow();
}

Game_Engine::~Game_Engine()
{
	delete this->window;
}


void Game_Engine::initWindow()
{
	this->videoMode = sf::VideoMode(sf::VideoMode::getDesktopMode().width * 0.5f, sf::VideoMode::getDesktopMode().height * 0.7f);
	this->window = new sf::RenderWindow(this->videoMode, "Template", sf::Style::Close | sf::Style::Titlebar);

	this->window->setFramerateLimit(60);
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
	this->CollisionDetection();
}

void Game_Engine::Render()
{
	this->window->clear();

	this->window->display();
}
