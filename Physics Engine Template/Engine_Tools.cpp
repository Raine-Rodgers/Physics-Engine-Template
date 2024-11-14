#include "Engine_Tools.h"


Engine_Tools::Engine_Tools()
{
}

Engine_Tools::~Engine_Tools()
{
}


bool Engine_Tools::DetectCollisionCircleToRectangle(sf::CircleShape circle, sf::RectangleShape rectangle)
{
    float rectHalfWidth = rectangle.getSize().x / 2;
    float rectHalfHeight = rectangle.getSize().y / 2;
    
    float deltaX = circle.getPosition().x - rectangle.getPosition().x;
    float deltaY = circle.getPosition().y - rectangle.getPosition().y;
    
    float circleDistanceXRotated = abs(deltaX * cos(rectangle.getRotation() * 3.14159 / 180) + deltaY * sin(rectangle.getRotation() * 3.14159 / 180));
    float circleDistanceYRotated = abs(deltaY * cos(rectangle.getRotation() * 3.14159 / 180) - deltaX * sin(rectangle.getRotation() * 3.14159 / 180));
    
    if (circleDistanceXRotated > (rectHalfWidth + circle.getRadius()))
    {
        return false;
    }
    
    if (circleDistanceYRotated > (rectHalfHeight + circle.getRadius()))
    {
        return false;
    }
    
    if (circleDistanceXRotated <= rectHalfWidth)
    {
        return true;
    }
    
    if (circleDistanceYRotated <= rectHalfHeight)
    {
        return true;
    }
    
    float cornerDistanceSq = pow(circleDistanceXRotated - rectHalfWidth, 2) +
                             pow(circleDistanceYRotated - rectHalfHeight, 2);
    
    return (cornerDistanceSq <= pow(circle.getRadius(), 2));
}
