#pragma once
#include "Manager.h"
#include "Utils.h"
#include "GameManager.h"

using vector2f = CustomVector2f;

class CollisionManager :
    public Manager
{
    public:
		CollisionManager(GameManager* gm);

		Player* player = nullptr;
		std::list<CACEnemy*>* cacEnemy;
		std::list<ShooterEnemy*>* shooterEnemy;

		GameManager* gameManager;
		void Update( float deltaTime);

		void CheckCollisionsSquareTriangle(vector2f square[4], vector2f triangle[3]);
		void CheckCollisionsTriangleTriangle(vector2f triangle1[3], vector2f triangle2[3]);
		void CheckCollisionsCircleSquare(sf::CircleShape, vector2f square[4]);

		bool IsPointInTriangle(vector2f point, vector2f triangle[3]);
};

