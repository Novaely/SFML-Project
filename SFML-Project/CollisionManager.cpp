#include "CollisionManager.h"


CollisionManager::CollisionManager(GameManager* gm)
{
	gameManager = gm;
	player = gm->player;
	cacEnemy = gm->cacEnemy;
	shooterEnemy = gm->shooterEnemy;
}

void CollisionManager::Update(float deltaTime)
{

	for (int i = 0; i < cacEnemy.size(); i++)
	{
		 //CheckCollisionsSquareTriangle(cacEnemy[i], player);
	}
	CheckCollisionsSquareTriangle(nullptr, nullptr);
}

void CollisionManager::CheckCollisionsSquareTriangle(vector2f square[4], vector2f triangle[3])
{
	float rw = square[1].x - square[0].x; // width
	float rh = square[3].y - square[0].y; // height
	float rx = square[0].x; // x position
	float ry = square[0].y; // y position

	// Triangle -> Square
	for (int i = 0; i < 3; i++)
	{
		if ((triangle[i].y >= ry && triangle[i].y <= rh + ry) && (triangle[i].x >= rx && triangle[i].x <= rw + rx))
		{
			std::cout << "Collision detected" << std::endl;
		}

	}

	// Square -> Triangle
	for (int i = 0; i < 4; i++)
	{

        if (IsPointInTriangle(square[i], triangle))
        {
			std::cout << "Collision detected" << std::endl;
        }
	}

}
void CollisionManager::CheckCollisionsTriangleTriangle(vector2f triangle1[3], vector2f triangle2[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (IsPointInTriangle(triangle1[i], triangle2))
		{
			std::cout << "Collision detected" << std::endl;
		}
		if (IsPointInTriangle(triangle2[i], triangle1))
		{
			std::cout << "Collision detected" << std::endl;
		}
	}
}

void CollisionManager::CheckCollisionsCircleSquare(sf::CircleShape circle, vector2f square[4])
{
	float rw = square[1].x - square[0].x; // width
	float rh = square[3].y - square[0].y; // height
	float rx = square[0].x; // x position
	float ry = square[0].y; // y position
	float cr = circle.getRadius(); // circle radius
	float cx = circle.getPosition().x + cr; // circle x position (center)
	float cy = circle.getPosition().y + cr; // circle y position (center)

	if (((cx - cr >= rx && cx + cr <= rw + rx) && (cy - cr >= ry && cy + cr <= ry + rh)) && (cx - cr < rx && cx + cr > rw + rx) && (cy - cr < ry && cy + cr > ry + rh))
	{
		std::cout << "Collision detected" << std::endl;
	}

}


bool CollisionManager::IsPointInTriangle(vector2f point, vector2f triangle[3])
{
	vector2f AB = triangle[1] - triangle[0];
	vector2f BC = triangle[2] - triangle[1];
	vector2f CA = triangle[0] - triangle[2];

	vector2f n1 = vector2f(-AB.y, AB.x);
	vector2f n2 = vector2f(-BC.y, BC.x);
	vector2f n3 = vector2f(-CA.y, CA.x);

	vector2f ABP = point - triangle[0] + AB * 0.5f;
	vector2f BCP = point - triangle[1] + BC * 0.5f;
	vector2f CAP = point - triangle[2] + CA * 0.5f;

	if (ABP.Dot(n1) > 0)
	{
		return false;
	}
	if (BCP.Dot(n2) > 0)
	{
		return false;
	}
	if (CAP.Dot(n3) > 0)
	{
		return false;
	}

	return true;
}