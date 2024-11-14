#include "Engine_Tools.h"


Engine_Tools::Engine_Tools()
{
}

Engine_Tools::~Engine_Tools()
{
}

void Engine_Tools::DetectCollisionCircleToCircle(sf::CircleShape* circle1, sf::CircleShape* circle2)
{
	float distance = sqrt(pow(circle1->getPosition().x - circle2->getPosition().x, 2) + pow(circle1->getPosition().y - circle2->getPosition().y, 2));
	float radiusSum = circle1->getRadius() + circle2->getRadius();

	if (distance < radiusSum)
	{
		std::cout << "Collision Detected" << std::endl;
	}
}

bool Engine_Tools::IntersectPolygons(sf::Vector2f poly1, sf::Vector2f poly2)
{
	for(int i=0; i<poly1)
}
