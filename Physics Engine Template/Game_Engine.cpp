#include "Game_Engine.h"


Game_Engine::Game_Engine() // constructor just calls the init functions to clean up the code a bit and make it easier to read
{
	this->initWindow();
	this->initVariables();
}

Game_Engine::~Game_Engine()
{
	delete this->window;
}

void Game_Engine::initWindow() // initializes the window with the title and size
{
	// sf::VideoMode::getDesktopMode().width * 0.5f, sf::VideoMode::getDesktopMode().height * 0.7f
	this->videoMode = sf::VideoMode(900, 900);
	this->window = new sf::RenderWindow(this->videoMode, "Template", sf::Style::Close | sf::Style::Titlebar);
	

	this->window->setFramerateLimit(60);
}

void Game_Engine::initVariables() // basic initialization function
{
	gravity = 0.f; // higher number = more gravity
	drag = 0.95f; // higher number = less drag
	engineTools = Engine_Tools();
	rectangleA = new Rigid_Body_Rectangle(true, true, sf::Vector2f(200, 500), 0);
	rectangleA->SetColor(sf::Color::Green);
	rectangleA->SetRotation(45);
	rectangleA->SetPosition(sf::Vector2f(150, 400));
	rectangleB = new Rigid_Body_Rectangle(false, true, sf::Vector2f(200, 300), 0);
	rectangleB->SetColor(sf::Color::Blue);

}

void Game_Engine::PollEvents()
{
	while (this->window->pollEvent(this->event)) // for now this is just for closing the window. might add more later but i doubt it
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
	sf::Vector2f rectBvel = sf::Vector2f(rectangleB->GetVelocity().x * drag, rectangleB->GetVelocity().y * drag);
	rectangleB->SetVelocity(rectBvel);
	//if (rectangleB->GetVelocity().x < 0.001f) // either this is janked or my math is terrible but either way i hate it
	//{
	//	rectangleB->SetVelocity(sf::Vector2f(0, rectangleB->GetVelocity().y)); // if the velocity is below a certain value set it to 0 to reduce compuation amount
	//	std::cout << "it happened" << std::endl;
	//}
	
	
}

void Game_Engine::CollisionUpdate()
{
	sf::Vector2f normal;
	float depth;
	std::vector<sf::Vector2f> verticesA = rectangleA->GetVertices(rectangleA->GetPointCount());
	std::vector<sf::Vector2f> verticesB = rectangleB->GetVertices(rectangleB->GetPointCount());
	if (engineTools.SATPolygonCollision(verticesA, verticesB, normal, depth)) { rectangleA->SetLockedPosition(false); }
	if (!(rectangleA->GetCollidable() || rectangleB->GetCollidable())) // if either object is not collidable
	{
		return;
	}
	if (engineTools.SATPolygonCollision(verticesA, verticesB, normal, depth))
	{
		if (!(rectangleA->GetLockedPosition() || rectangleB->GetLockedPosition())) // if neither object is locked
		{
			rectangleA->SetPosition(rectangleA->GetRectangle().getPosition() + normal * depth / 2.f); // move each object half the depth
			rectangleB->SetPosition(rectangleB->GetRectangle().getPosition() - normal * depth / 2.f);
			rectangleA->SetVelocity(rectangleA->GetVelocity() - normal * (normal.x * rectangleA->GetVelocity().x + normal.y * rectangleA->GetVelocity().y)); // apply the normal to the velocity
			rectangleB->SetVelocity(rectangleB->GetVelocity() - normal * (normal.x * rectangleB->GetVelocity().x + normal.y * rectangleB->GetVelocity().y));
			return; // return to prevent further calculations
		}
		if (rectangleA->GetLockedPosition() && rectangleB->GetLockedPosition()) // if both objects are locked
		{
			return;
		}
		if (rectangleA->GetLockedPosition()) // if object A is locked
		{
			rectangleB->SetPosition(rectangleB->GetRectangle().getPosition() - normal * depth); // move object B the full depth
			rectangleB->SetVelocity(rectangleB->GetVelocity() - normal * (normal.x * rectangleB->GetVelocity().x + normal.y * rectangleB->GetVelocity().y));
			return;
		}
		if (rectangleB->GetLockedPosition()) // if object B is locked
		{
			rectangleA->SetPosition(rectangleA->GetRectangle().getPosition() + normal * depth); // move object A the full depth
			rectangleA->SetVelocity(rectangleA->GetVelocity() - normal * (normal.x * rectangleA->GetVelocity().x + normal.y * rectangleA->GetVelocity().y));
			return;
		}
	}
}

void Game_Engine::Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // moves the object left
	{
		rectangleB->SetVelocity(sf::Vector2f(rectangleB->GetVelocity().x - 0.1f, rectangleB->GetVelocity().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // moves the object right
	{
		rectangleB->SetVelocity(sf::Vector2f(rectangleB->GetVelocity().x + 0.1f, rectangleB->GetVelocity().y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // moves the object up
	{
		rectangleB->SetVelocity(sf::Vector2f(rectangleB->GetVelocity().x, rectangleB->GetVelocity().y - 0.1f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // moves the object down
	{
		rectangleB->SetVelocity(sf::Vector2f(rectangleB->GetVelocity().x, rectangleB->GetVelocity().y + 0.1f));
	}
}

void Game_Engine::Update()
{
	PhysicsUpdate();
	CollisionUpdate();
	this->rectangleA->Update(gravity);
	this->rectangleB->Update(gravity);
	PollEvents();
	Movement();
	std::cout << "rectangleB velocity: " << rectangleB->GetVelocity().x << ", " << rectangleB->GetVelocity().y << std::endl;
}

void Game_Engine::Render()
{
	this->window->clear(sf::Color(46, 74, 94)); // clears the frame and sets the color of the window the rgb value specified

	rectangleA->Render(this->window); // call the render function of the object and pass the window pointer to it

	rectangleB->Render(this->window);

	this->window->display(); // displayed the frame with the updated information
}


