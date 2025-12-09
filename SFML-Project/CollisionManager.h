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
		bool CheckCollisionsTriangleTriangle(const sf::ConvexShape& trian1, const sf::ConvexShape& trian2);
		bool CheckCollisionsCircleSquare(const sf::CircleShape& circle, const sf::RectangleShape& rect);
		bool CheckCollisionsCircleTriangle(const sf::CircleShape& circle, const sf::ConvexShape& trian);

		bool IsPointInConvexShape(const Vec2f& point, Vec2f shapePoints[], Vec2f convNormals[], int numNormals);
		bool IsPointInTriangle(const Vec2f& point, Vec2f triangle[3]);
		float DistancePointToSegment(const Vec2f& point, const Vec2f& start, const Vec2f& end);
		float dotProduct(float vx1, float vy1, float vx2, float vy2);
};

