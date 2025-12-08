#pragma once
#include "Manager.h"
#include "Utils.h"
#include "GameManager.h"

using vector2f = CustomVector2f;

class CollisionManager :
    public Manager
{
    public:
		CollisionManager(GameManager* gm, CustomVector2f windowSize);

		Player* player = nullptr;
		std::list<CACEnemy*>* cacEnemy;
		std::list<ShooterEnemy*>* shooterEnemy;
		std::list<TurretEnemy*>* turretEnemy;
		std::list<Bullet*>* bullets;
		std::list<Collectible*>* collectibles;
		sf::ConvexShape* pShape;
		sf::Shape* windowShape;

		GameManager* gameManager;
		void Update( float deltaTime);
	private: 
		bool CheckCollisionsSquareTriangle(sf::RectangleShape rect, sf::ConvexShape trian);
		bool CheckCollisionsTriangleTriangle(sf::ConvexShape trian1, sf::ConvexShape trian2);
		bool CheckCollisionsCircleSquare(sf::CircleShape circle, sf::RectangleShape rect);
		bool CheckCollisionsCircleTriangle(sf::CircleShape& circle, sf::ConvexShape& trian);

		bool IsPointInTriangle(vector2f point, vector2f triangle[3]);
		float DistancePointToSegment(vector2f point, vector2f start, vector2f end);
		float dotProduct(float vx1, float vy1, float vx2, float vy2);
};

