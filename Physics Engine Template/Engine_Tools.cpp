#include "Engine_Tools.h"


Engine_Tools::Engine_Tools()
{
}

Engine_Tools::~Engine_Tools()
{
}


bool Engine_Tools::SATPolygonCollision(std::vector<sf::Vector2f> verticesA, std::vector<sf::Vector2f> verticesB)
{
    float minA = 0;
    float maxA = 0;
    float minB = 0;
    float maxB = 0;

    for (int i = 0; i < verticesA.size(); i++) 
    {
        sf::Vector2f edgeVertexA = verticesA[i];
        sf::Vector2f edgeVertexB = verticesA[(i + 1) % verticesA.size()];

        sf::Vector2f edge = edgeVertexB - edgeVertexA;
        sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);

        ProjectVerticesToAxis(verticesA, axis, minA, maxA);
        ProjectVerticesToAxis(verticesB, axis, minB, maxB);

        if (minA > maxB || minB > maxA)
        {
			return false;
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

//{
//	sf::Vector2f p1 = verticesA[i];
//	sf::Vector2f p2 = verticesA[(i + 1) % verticesA.size()];
//	sf::Vector2f normal = sf::Vector2f(p2.y - p1.y, p1.x - p2.x);
//	float minA = 0;
//	float maxA = 0;
//	for (int j = 0; j < verticesA.size(); j++)
//	{
//		float projected = normal.x * verticesA[j].x + normal.y * verticesA[j].y;
//		if (j == 0)
//		{
//			minA = projected;
//			maxA = projected;
//		}
//		else
//		{
//			if (projected < minA)
//				minA = projected;
//			if (projected > maxA)
//				maxA = projected;
//		}
//	}
//	float minB = 0;
//	float maxB = 0;
//	for (int j = 0; j < verticesB.size(); j++)
//	{
//		float projected = normal.x * verticesB[j].x + normal.y * verticesB[j].y;
//		if (j == 0)
//		{
//			minB = projected;
//			maxB = projected;
//		}
//		else
//		{
//			if (projected < minB)
//				minB = projected;
//			if (projected > maxB)
//				maxB = projected;
//		}
//	}
//	if (maxA < minB || maxB < minA)
//		return false;
//}
