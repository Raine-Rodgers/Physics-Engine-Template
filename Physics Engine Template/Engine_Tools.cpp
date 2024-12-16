#include "Engine_Tools.h"


Engine_Tools::Engine_Tools()
{
}

Engine_Tools::~Engine_Tools()
{
}


////////////////////// COLLISION FUNCTIONS //////////////////////

bool Engine_Tools::SATPolygonCollision(std::vector<sf::Vector2f> verticesA, std::vector<sf::Vector2f> verticesB, sf::Vector2f& normal, float& depth)
{
    float minA, maxA, minB, maxB;
    normal = sf::Vector2f(0, 0);
    depth = float(INT_MAX);

    for (int i = 0; i < verticesA.size(); i++) // loops through all the vertices of the first polygon
    {
        sf::Vector2f edgeVertexA = verticesA[i];
        sf::Vector2f edgeVertexB = verticesA[(i + 1) % verticesA.size()]; // finds 2 connected vertices to calculate normal with

        sf::Vector2f edge = edgeVertexB - edgeVertexA;
        sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);

        ProjectVerticesToAxis(verticesA, axis, minA, maxA);
        ProjectVerticesToAxis(verticesB, axis, minB, maxB); // projects both polygons to the axis and returns their min and max values to check for overlap

        if (minA > maxB || minB > maxA)
        {
			return false; //if any gap is detected then the loop breaks immediately
		}

        float axisDepth = MinValue(maxB - minA, maxA - minB); // calculates the depth of the overlap

        if (axisDepth < depth) // if the depth is smaller than the current depth then it updates the depth and normal
		{
			depth = axisDepth;
			normal = axis;
		}

    }
    //////////////////// Vertices B Loop ////////////////////

    for (int i = 0; i < verticesB.size(); i++)
    {
        sf::Vector2f edgeVertexA = verticesB[i];
        sf::Vector2f edgeVertexB = verticesB[(i + 1) % verticesB.size()];

        sf::Vector2f edge = edgeVertexB - edgeVertexA;
        sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);

        ProjectVerticesToAxis(verticesA, axis, minA, maxA);
        ProjectVerticesToAxis(verticesB, axis, minB, maxB);

        if (minA > maxB || minB > maxA)
        {
            return false;
        }

        float axisDepth = MinValue(maxB - minA, maxA - minB); // calculates the depth of the overlap

        if (axisDepth < depth) // if the depth is smaller than the current depth then it updates the depth and normal
        {
            depth = axisDepth;
            normal = axis;
        }
    }

    depth /= Length(normal);
    normal = Normalize(normal);

    sf::Vector2f centerA = ArithmaticMean(verticesA);
    sf::Vector2f centerB = ArithmaticMean(verticesB);

    sf::Vector2f centerDirection = centerA - centerB;

    if (DotProduct(centerDirection, normal) < 0.f) // if the center direction is less than 0 then the normal is flipped
	{
		normal = -normal;
	}

    return true;
}

bool Engine_Tools::SATCircleToPolyCollision(sf::Vector2f circleCenter, float circleRadius, std::vector<sf::Vector2f> vertices, sf::Vector2f& normal, float& depth)
{
    float minA, maxA, minB, maxB;
    normal = sf::Vector2f(0, 0);
    depth = float(INT_MAX);


    for (int i = 0; i < vertices.size(); i++) // loops through all the vertices of the first polygon
    {
        sf::Vector2f edgeVertexA = vertices[i];
        sf::Vector2f edgeVertexB = vertices[(i + 1) % vertices.size()]; // finds 2 connected vertices to calculate normal with

        sf::Vector2f edge = edgeVertexB - edgeVertexA;
        sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);

        ProjectVerticesToAxis(vertices, axis, minA, maxA);
        ProjectCircleToAxis(circleCenter, circleRadius, axis, minB, maxB);

        if (minA > maxB || minB > maxA)
        {
            return false; //if any gap is detected then the loop breaks immediately
        }

        float axisDepth = MinValue(maxB - minA, maxA - minB); // calculates the depth of the overlap

        if (axisDepth < depth) // if the depth is smaller than the current depth then it updates the depth and normal
        {
            depth = axisDepth;
            normal = axis;
        }

    }

    int closestPointIndex = FindClosesPointToCircle(circleCenter, vertices);
    sf::Vector2f closestPoint = vertices[closestPointIndex];


    sf::Vector2f axis = closestPoint - circleCenter;

    ProjectVerticesToAxis(vertices, axis, minA, maxA);
    ProjectCircleToAxis(circleCenter, circleRadius, axis, minB, maxB);

    if (minA > maxB || minB > maxA)
    {
        return false; //if any gap is detected then the loop breaks immediately
    }

    float axisDepth = MinValue(maxB - minA, maxA - minB); // calculates the depth of the overlap

    if (axisDepth < depth) // if the depth is smaller than the current depth then it updates the depth and normal
    {
        depth = axisDepth;
        normal = axis;
    }

    depth /= Length(normal);
    normal = Normalize(normal);

    sf::Vector2f polygonCenter = ArithmaticMean(vertices);

    sf::Vector2f centerDirection = polygonCenter - circleCenter;

    if (DotProduct(centerDirection, normal) < 0.f)
    {
        normal = -normal;
    }

    return true;
}

bool Engine_Tools::CircleCollision(sf::Vector2f circleCenterA, float circleRadiusA, sf::Vector2f circleCenterB, float circleRadiusB, sf::Vector2f& normal, float& depth)
{
    float distance = Distance(circleCenterA, circleCenterB);
    float radii = circleRadiusA + circleRadiusB;

    normal = sf::Vector2f(0, 0);
    depth = float(INT_MIN);

    depth = radii - distance;

    if (distance >= radii)
    {
		return false;
	}

    normal = Normalize(circleCenterA - circleCenterB);
    depth = radii - distance;

	return true;
}



////////////////////// PROJECTION FUNCTIONS //////////////////////

void Engine_Tools::ProjectVerticesToAxis(std::vector<sf::Vector2f> vertices, sf::Vector2f axis, float& min, float& max) // usage of reference & alows me to change their values without using the return statement
{
    min = float(INT_MAX);
    max = float(INT_MIN);

    for (int i = 0; i < vertices.size(); i++)
    {
        sf::Vector2f currentVertex = vertices[i];
        float projection = DotProduct(currentVertex, axis);

        if (projection < min) { min = projection; }
        if (projection > max) { max = projection; }
	}
}

void Engine_Tools::ProjectCircleToAxis(sf::Vector2f circleCenter, float circleRadius, sf::Vector2f axis, float& min, float& max)
{ // using reference & on min and max lets me change the values without the usage of a return statement
    sf::Vector2f direction = Normalize(axis);
    sf::Vector2f directionAndRadius = direction * circleRadius;

    sf::Vector2f point1 = circleCenter + directionAndRadius;
    sf::Vector2f point2 = circleCenter - directionAndRadius;

    min = DotProduct(point1, axis);
    max = DotProduct(point2, axis);

    if (min > max)
    {
		float temp = min;
		min = max;
		max = temp;
	}
}


////////////////////// MISC FUNCTIONS //////////////////////

int Engine_Tools::FindClosesPointToCircle(sf::Vector2f circleCenter, std::vector<sf::Vector2f> vertices)
{
    int closestIndex = -1;
    float minDistance = float(INT_MAX);

    for (int i = 0; i < vertices.size(); i++)
    {
		sf::Vector2f currentVertex = vertices[i];
		float distance = Distance(circleCenter, currentVertex);

        if (distance < minDistance)
        {
			minDistance = distance;
			closestIndex = i;
		}
	}
    
	return closestIndex;
}


////////////////////// MATH FUNCTIONS //////////////////////

float Engine_Tools::MinValue(float a, float b)
{
    if (a < b) { return a; }
	else { return b; }
}

float Engine_Tools::MaxValue(float a, float b)
{
    if (a > b) return a;
	else return b;
}

float Engine_Tools::DotProduct(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

float Engine_Tools::Length(sf::Vector2f a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

float Engine_Tools::Distance(sf::Vector2f a, sf::Vector2f b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

sf::Vector2f Engine_Tools::Normalize(sf::Vector2f a)
{
    float invLen = 1.f / sqrt(a.x * a.x + a.y * a.y);
    return sf::Vector2f(a.x * invLen, a.y * invLen);
}

sf::Vector2f Engine_Tools::ArithmaticMean(std::vector<sf::Vector2f> vertices)
{
    float sumX = 0;
    float sumY = 0;

    for(int i = 0; i < vertices.size(); i++)
	{
		sf::Vector2f currentVertex = vertices[i];
        sumX += currentVertex.x;
        sumY += currentVertex.y;
	}

	return sf::Vector2f(sumX / vertices.size(), sumY / vertices.size());
}
