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
    float minA;
    float maxA;
    float minB;
    float maxB;
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

    if (DotProduct(centerDirection, normal) < 0.f)
	{
		normal = -normal;
	}

    return true;
}


void Engine_Tools::ProjectVerticesToAxis(std::vector<sf::Vector2f> vertices, sf::Vector2f axis, float& min, float& max)
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
