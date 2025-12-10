#pragma once
#include "Manager.h"
#include "Utils.h"
#include "GameManager.h"

class CollisionManager :
    public Manager
{
    public:
		CollisionManager(GameManager* gm, CustomVector2f windowSize);

		std::list<GameObject*>* gameObjects;
		sf::Shape* windowShape;

		GameManager* gameManager;
		void Update( float deltaTime);
	private: 
		bool CheckCollisionPair(GameObject* goA, GameObject* goB);
		bool CanCollide(GameObject* goA, GameObject* goB);
		bool AreInDistance(GameObject* goA, GameObject* goB);

		bool CheckCollisionsSquareTriangle(const sf::RectangleShape& rect, const sf::ConvexShape& trian);
		bool CheckCollisionsTriangleTriangle(const sf::ConvexShape& trian1, const sf::ConvexShape& trian2);
		bool CheckCollisionsCircleRectangle(const sf::CircleShape& circle, const sf::RectangleShape& rect);
		bool CheckCollisionsCircleTriangle(const sf::CircleShape& circle, const sf::ConvexShape& trian);

		bool IsPointInConvexShape(const Vec2f& point, const std::vector<Vec2f>& shapePoints, const std::vector<Vec2f>& convNormals);
		bool IsPointInTriangle(const Vec2f& point, Vec2f triangle[3]);
		float DistancePointToSegment(const Vec2f& point, const Vec2f& start, const Vec2f& end);
		float dotProduct(float vx1, float vy1, float vx2, float vy2);
};