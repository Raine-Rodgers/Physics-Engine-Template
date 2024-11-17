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
	this->gravity = 0.1f;
	this->drag = 0.5f;
	this->engineTools = Engine_Tools();
	this->rectangleA = new Rigid_Body_Rectangle(true, sf::Vector2f(200, 500), 0);
	this->rectangleA->SetColor(sf::Color::Green);
	this->rectangleB = new Rigid_Body_Rectangle(false, sf::Vector2f(200, 300), 0);
	this->rectangleB->SetColor(sf::Color::Blue);
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


void Game_Engine::PhysicsUpdate()
{
	sf::Vector2f point(0.f, 0.f);
	sf::Vector2f transformedPoint = this->rectangleA->GetTransformedPoint(0);
	
}


void Game_Engine::Update()
{
	this->PhysicsUpdate();
	this->rectangleA->Update(this->gravity);
	this->rectangleB->Update(this->gravity);
	this->PollEvents();
}

void Game_Engine::Render()
{
	this->window->clear();

	this->rectangleA->Render(this->window);

	this->rectangleB->Render(this->window);

	this->window->display();
}

