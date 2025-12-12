#pragma once
#include "Manager.h"
#include "Utils.h"
#include "GameManager.h"

class CollisionManager :
    public Manager
{
    public:
		// Constructor
		CollisionManager(CustomVector2f windowSize);

		// Function
		void Update( float deltaTime);
	private: 
		// Variable
		GameManager* _gameManager = nullptr;
		std::list<GameObject*>* _gameObjects;
		sf::Shape* _windowShape;

		struct ConvexShapeInfo
		{
			const sf::RectangleShape* rectShape = nullptr;
			const sf::ConvexShape* convexShape = nullptr;
			int numPoints = 0;
			std::vector<Vec2f> points;
			std::vector<Vec2f> normals;

			void ComputPointsAndNormals();
		};

		// Function 
		bool CheckCollisionPair(GameObject* goA, GameObject* goB);
		bool CanCollide(GameObject* goA, GameObject* goB);
		bool AreInDistance(GameObject* goA, GameObject* goB);

		bool CheckCollisionsSquareTriangle(const sf::RectangleShape& rect, const sf::ConvexShape& trian);
		bool CheckCollisionsTriangleTriangle(const sf::ConvexShape& trian1, const sf::ConvexShape& trian2);
		bool CheckCollisionsCircleRectangle(const sf::CircleShape& circle, const sf::RectangleShape& rect);
		bool CheckCollisionsCircleTriangle(const sf::CircleShape& circle, const sf::ConvexShape& trian);

		bool IsPointInConvexShape(const Vec2f& point, const std::vector<Vec2f>& shapePoints, const std::vector<Vec2f>& convNormals);
		float DistancePointToSegment(const Vec2f& point, const Vec2f& start, const Vec2f& end);
};