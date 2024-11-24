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
	gravity = 0.1f;
	drag = 0.5f;
	engineTools = Engine_Tools();
	rectangleA = new Rigid_Body_Rectangle(true, sf::Vector2f(200, 500), 0);
	rectangleA->SetColor(sf::Color::Green);
	rectangleA->SetRotation(45);
	rectangleA->SetPosition(sf::Vector2f(150, 500));
	rectangleB = new Rigid_Body_Rectangle(false, sf::Vector2f(200, 300), 0);
	rectangleB->SetColor(sf::Color::Blue);

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
				if (this->event.key.code == sf::Keyboard::W)
					PhysicsUpdate();
				break;
		}
	}
}


void Game_Engine::PhysicsUpdate()
{
	std::vector<sf::Vector2f> verticesA = rectangleA->GetVertices(rectangleA->GetPointCount());
	std::vector<sf::Vector2f> verticesB = rectangleB->GetVertices(rectangleB->GetPointCount());
	if (engineTools.SATPolygonCollision(verticesA, verticesB)) { rectangleB->SetVelocity(sf::Vector2f(0, 0)); gravity = 0.f; }
}


void Game_Engine::Update()
{
	PhysicsUpdate();
	this->rectangleA->Update(gravity);
	this->rectangleB->Update(gravity);
	PollEvents();
}

void Game_Engine::Render()
{
	this->window->clear();

	rectangleA->Render(this->window);

	rectangleB->Render(this->window);

	this->window->display();
}

