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
	drag = 0.99f; // higher number = less drag
	engineTools = Engine_Tools();
	objectList = std::vector<Rigid_Body*>();

	rectangleA = new Rigid_Body(false, true, 1);
	//rectangleA->SetSize(sf::Vector2f(100, 50));
	rectangleA->SetColor(sf::Color::Red);
	rectangleA->SetPosition(sf::Vector2f(400, 400));
	rectangleA->SetRadius(50);
	rectangleA->SetOrigin();

	rectangleB = new Rigid_Body(false, true, 1);
	rectangleB->SetSize(sf::Vector2f(100, 50));
	rectangleB->SetColor(sf::Color::Green);
	rectangleB->SetPosition(sf::Vector2f(400, 500));
	rectangleB->SetRadius(50);
	rectangleB->SetOrigin();

	orgin = new Rigid_Body(true, false, 1);
	orgin->SetPosition(rectangleA->GetPosition());
	orgin->SetRadius(5);
	orgin->SetOrigin();


	objectList.push_back(rectangleA);
	objectList.push_back(rectangleB);
	//objectList.push_back(orgin);


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

void Game_Engine::CollisionResolve(int indexShapeA, int indexShapeB, sf::Vector2f normal, float depth)
{
	sf::Vector2f relativeVelocity = objectList[indexShapeB]->GetVelocity() - objectList[indexShapeA]->GetVelocity(); // calculates the relative velocity

	float e = engineTools.MinValue(objectList[indexShapeA]->GetRestitution(), objectList[indexShapeB]->GetRestitution()); // calculates the restitution

	float j = -(1 + e) * engineTools.DotProduct(relativeVelocity, normal);


	//j /= (engineTools.DotProduct(normal, normal) * (1 / objectList[indexShapeA]->_mass + 1 / objectList[indexShapeB]->_mass)); // calculates the impulse
	j /= (1.f / objectList[indexShapeA]->_mass + (1.f / objectList[indexShapeB]->_mass)); // calculates the impulse


	//objectList[indexShapeA]->SetVelocity({5, 5});

	if (!(objectList[indexShapeA]->GetCollidable() || objectList[indexShapeB]->GetCollidable())) // if either object is not collidable
	{
		return;
	}
	if (objectList[indexShapeA]->GetLockedPosition() && objectList[indexShapeB]->GetLockedPosition()) // if both objects are locked
	{
		return;
	}
	if (!(objectList[indexShapeA]->GetLockedPosition() || objectList[indexShapeB]->GetLockedPosition())) // if neither object is locked
	{
		objectList[indexShapeA]->SetPosition(objectList[indexShapeA]->GetPosition() + normal * depth / 2.f); // move each object half the depth
		objectList[indexShapeB]->SetPosition(objectList[indexShapeB]->GetPosition() - normal * depth / 2.f);

		objectList[indexShapeA]->SetVelocity(objectList[indexShapeA]->GetVelocity() - j / objectList[indexShapeA]->_mass * normal); // applies the impulse to the velocity
		objectList[indexShapeB]->SetVelocity(objectList[indexShapeB]->GetVelocity() + j / objectList[indexShapeB]->_mass * normal);

		//objectList[indexShapeA]->SetVelocity(objectList[indexShapeA]->GetVelocity() - normal * (normal.x * objectList[indexShapeA]->GetVelocity().x + normal.y * objectList[indexShapeA]->GetVelocity().y)); // apply the normal to the velocity
		//objectList[indexShapeB]->SetVelocity(objectList[indexShapeB]->GetVelocity() - normal * (normal.x * objectList[indexShapeB]->GetVelocity().x + normal.y * objectList[indexShapeB]->GetVelocity().y));
		return; // return to prevent further calculations
	}
	if (objectList[indexShapeA]->GetLockedPosition()) // if object A is locked
	{
		objectList[indexShapeB]->SetPosition(objectList[indexShapeB]->GetPosition() - normal * depth); // move object B the full depth
		objectList[indexShapeB]->SetVelocity(objectList[indexShapeB]->GetVelocity() - normal * (normal.x * objectList[indexShapeB]->GetVelocity().x + normal.y * objectList[indexShapeB]->GetVelocity().y));
		return;
	}
	if (objectList[indexShapeB]->GetLockedPosition()) // if object B is locked
	{
		///////////// CHANGE " + NORMAL" TO "- NORMAL" IF HAVING COLLISION ISSUE //////////////
		objectList[indexShapeA]->SetPosition(objectList[indexShapeA]->GetPosition() + normal * depth); // move object A the full depth
		objectList[indexShapeA]->SetVelocity(objectList[indexShapeA]->GetVelocity() - normal * (normal.x * objectList[indexShapeA]->GetVelocity().x + normal.y * objectList[indexShapeA]->GetVelocity().y));
		return;
	}
}

void Game_Engine::CollisionCheck()
{
	sf::Vector2f normal;
	float depth;

	for (int i = 0; i < objectList.size(); i++) // loops through the object list and checks for collisions
	{
		for (int k = i + 1; k < objectList.size(); k++)
		{
			if (objectList[i]->GetShapeType() == 0 && objectList[k]->GetShapeType() == 0) // if both objects are rectangles
			{
				std::vector<sf::Vector2f> verticesA =		objectList[i]->GetVertices(objectList[i]->GetPointCount()); // create an array of vertices for each object
				std::vector<sf::Vector2f> verticesB =		objectList[k]->GetVertices(objectList[k]->GetPointCount());
				if (engineTools.SATPolygonCollision(verticesA, verticesB, normal, depth)) { CollisionResolve(i, k, normal, depth); } // check for collision and resolve it
				//std::cout << "rect collision" << std::endl;
			}
			else if (objectList[i]->GetShapeType() == 0 && objectList[k]->GetShapeType() == 1) // if one object is a rectangle and the other a circle. might be able to make this prettier later
			{
				float circleRadius =						objectList[k]->GetRadius();
				sf::Vector2f circleCenter =					objectList[k]->GetPosition();
				std::vector<sf::Vector2f>vertices =			objectList[i]->GetVertices(objectList[i]->GetPointCount());
				if (engineTools.SATCircleToPolyCollision(circleCenter, circleRadius, vertices, normal, depth)) { CollisionResolve(i, k, normal, depth); }
				//std::cout << "rect and circ collision" << std::endl;
			}
			else if (objectList[i]->GetShapeType() == 1 && objectList[k]->GetShapeType() == 0) // if one object is a circle and the other a rectangle
			{
				float circleRadius =						objectList[i]->GetRadius();
				sf::Vector2f circleCenter =					objectList[i]->GetPosition();
				std::vector<sf::Vector2f> vertices =		objectList[k]->GetVertices(objectList[k]->GetPointCount());
				if (engineTools.SATCircleToPolyCollision(circleCenter, circleRadius, vertices, normal, depth)) { CollisionResolve(i, k, normal, depth); }
				
			}
			else if (objectList[i]->GetShapeType() == 1 && objectList[k]->GetShapeType() == 1) // if both objects are circles
			{
				float circleRadiusA =						objectList[i]->GetRadius();
				sf::Vector2f circleCenterA =				objectList[i]->GetPosition();
				sf::Vector2f circleCenterB =				objectList[k]->GetPosition();
				float circleRadiusB =						objectList[k]->GetRadius();
				if (engineTools.CircleCollision(circleCenterA, circleRadiusA, circleCenterB, circleRadiusB, normal, depth)) { CollisionResolve(i, k, normal, depth); }
				
			}
			
		}
	}

}

void Game_Engine::Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // moves the object left
	{
		//rectangleB->SetVelocity(sf::Vector2f(rectangleB->GetVelocity().x - 0.5f, rectangleB->GetVelocity().y));
		rectangleB->AddForce(sf::Vector2f(-0.5f, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // moves the object right
	{
		rectangleB->AddForce(sf::Vector2f(0.5f, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // moves the object up
	{
		rectangleB->AddForce(sf::Vector2f(0, -0.5f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // moves the object down
	{
		rectangleB->AddForce(sf::Vector2f(0, 0.5f));
	}
}

void Game_Engine::Update()
{
	PhysicsUpdate();
	CollisionCheck();
	
	orgin->SetPosition(rectangleA->GetPosition());

	for (int i = 0; i < objectList.size(); i++)
	{
		objectList[i]->Update(gravity);
	}
	PollEvents();
	Movement();
}

void Game_Engine::Render()
{
	this->window->clear(sf::Color(46, 74, 94)); // clears the frame and sets the color of the window the rgb value specified

	for (int i = 0; i < objectList.size(); i++) // iterates through the object list and renders each object
	{
		objectList[i]->Render(this->window);
	}

	this->window->display(); // displayed the frame with the updated information
}


