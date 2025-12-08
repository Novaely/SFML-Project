#pragma once
#include "Manager.h"
#include "Utils.h"
#include "GameManager.h"

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
		std::list<LightningNode*>* lightnings;
		std::list<Collectible*>* collectibles;
		sf::ConvexShape* pShape;
		sf::Shape* windowShape;

		GameManager* gameManager;
		void Update( float deltaTime);
	private: 
		bool CheckCollisionsSquareTriangle(const sf::RectangleShape& rect, const sf::ConvexShape& trian);
		bool CheckCollisionsTriangleTriangle(sf::ConvexShape trian1, sf::ConvexShape trian2);
		bool CheckCollisionsCircleSquare(sf::CircleShape circle, sf::RectangleShape rect);
		bool CheckCollisionsCircleTriangle(sf::CircleShape& circle, sf::ConvexShape& trian);

		bool IsPointInConvexShape(Vec2f point, Vec2f shapePoints[], Vec2f convNormals[], int numNormals);
		bool IsPointInTriangle(Vec2f point, Vec2f triangle[3]);
		float DistancePointToSegment(Vec2f point, Vec2f start, Vec2f end);
		float dotProduct(float vx1, float vy1, float vx2, float vy2);
};

