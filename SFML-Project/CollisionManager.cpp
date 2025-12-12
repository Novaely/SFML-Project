#include "CollisionManager.h"

CollisionManager::CollisionManager(CustomVector2f windowSize)
{
	_windowShape = new sf::RectangleShape();
	((sf::RectangleShape*)_windowShape)->setSize({ windowSize.x, windowSize.y});
	
	_gameManager = GameManager::GetInstance();

	_gameObjects = &(_gameManager->gameObjects);
}

void CollisionManager::Update(float deltaTime)
{
	auto itGoA = (*_gameObjects).begin();
	std::list<GameObject*>::iterator itGoB;
	while (itGoA != (*_gameObjects).end())
	{
		itGoB = std::next(itGoA);
		while (itGoB != (*_gameObjects).end())
		{
			if (CanCollide(*itGoA, *itGoB) && AreInDistance(*itGoA, *itGoB) && CheckCollisionPair(*itGoA, *itGoB))
			{
				(*itGoA)->OnCollisionEnter(*itGoB);
				(*itGoB)->OnCollisionEnter(*itGoA);
			}
			itGoB++;
		}
		itGoA++;
	}
}

void CollisionManager::ConvexShapeInfo::ComputPointsAndNormals()
{
	if (rectShape != nullptr)
	{
		Vec2f rectPos = rectShape->getPosition();
		float rectRotation = Math::ToRad(rectShape->getRotation());

		numPoints = rectShape->getPointCount();
		
		points.resize(numPoints, Vec2f::zero);
		normals.resize(numPoints, Vec2f::zero);

		for (int i = 0; i < numPoints; i++)
		{
			points[i] = Math::RotatePoint(rectShape->getPoint(i), Vec2f::zero, rectRotation) + rectPos;
		}

		int rectNextIndex;
		for (int i = 0; i < numPoints; i++)
		{
			rectNextIndex = (i + 1) % numPoints;
			normals[i] = (points[rectNextIndex] - points[i]).GetNormalClockWise().GetNormalised();
		}
		return;
	}
	if (convexShape != nullptr)
	{
		Vec2f trianPos = convexShape->getPosition();
		float trianRotation = Math::ToRad(convexShape->getRotation());

		numPoints = convexShape->getPointCount();
		points.resize(numPoints, Vec2f::zero);
		normals.resize(numPoints, Vec2f::zero);

		for (int i = 0; i < numPoints; i++)
		{
			points[i] = Math::RotatePoint(convexShape->getPoint(i), Vec2f::zero, trianRotation) + trianPos;
		}

		int trianNextIndex;
		for (int i = 0; i < numPoints; i++)
		{
			trianNextIndex = (i + 1) % numPoints;
			normals[i] = (points[trianNextIndex] - points[i]).GetNormalClockWise().GetNormalised();
		}
		return;
	}
}

bool CollisionManager::CheckCollisionPair(GameObject* goA, GameObject* goB)
{
	if (!goA->IsActive() || !goB->IsActive() || !goA->isAlive || !goB->isAlive) return false;

	switch (goA->shapeType)
	{
	// Shape A is Circle
	case ShapeType::Circle:
	{
		sf::CircleShape& goAShape = *static_cast<sf::CircleShape*>(goA->shape);

		switch (goB->shapeType)
		{
		case ShapeType::Circle:
			//std::cout << "Coll Circle with Circle not supported" << std::endl;
			return false;
		case ShapeType::Rectangle:
			return CheckCollisionsCircleRectangle(goAShape, *static_cast<sf::RectangleShape*>(goB->shape));
		case ShapeType::Convex:
			return CheckCollisionsCircleTriangle(goAShape, *static_cast<sf::ConvexShape*>(goB->shape));
		default:
			return false;
		}
		break;
	}
	// Shape A is Rectangle
	case ShapeType::Rectangle:
	{
		sf::RectangleShape& goAShape = *static_cast<sf::RectangleShape*>(goA->shape);

		switch (goB->shapeType)
		{
		case ShapeType::Circle:
			return CheckCollisionsCircleRectangle(*static_cast<sf::CircleShape*>(goB->shape), goAShape);
		case ShapeType::Rectangle:
			//std::cout << "Coll Rectangle with Rectangle not supported" << std::endl;
			return false;
		case ShapeType::Convex:
			return CheckCollisionsSquareTriangle(goAShape, *static_cast<sf::ConvexShape*>(goB->shape));
		default:
			return false;
		}
		break;
	}
	// Shape A is Convex
	case ShapeType::Convex:
	{
		sf::ConvexShape& goAShape = *static_cast<sf::ConvexShape*>(goA->shape);

		switch (goB->shapeType)
		{
		case ShapeType::Circle:
			return CheckCollisionsCircleTriangle(*static_cast<sf::CircleShape*>(goB->shape), goAShape);
		case ShapeType::Rectangle:
			return CheckCollisionsSquareTriangle(*static_cast<sf::RectangleShape*>(goB->shape), goAShape);
		case ShapeType::Convex:
			return CheckCollisionsTriangleTriangle(goAShape, *static_cast<sf::ConvexShape*>(goB->shape));
		default:
			return false;
		}
		break;
	}		
	default:
		return false;
	}
}

bool CollisionManager::CanCollide(GameObject* goA, GameObject* goB)
{
	return ((goA->layer & goB->collisionMask) != 0) && ((goB->layer & goA->collisionMask) != 0);
}

bool CollisionManager::AreInDistance(GameObject* goA, GameObject* goB)
{
	float rad = goA->broadRadius + goB->broadRadius;
	rad *= rad;
	float distSqrd = (goB->position - goA->position).GetSquaredMagnitude();

	return distSqrd <= rad;
}

bool CollisionManager::CheckCollisionsSquareTriangle(const sf::RectangleShape& rect, const sf::ConvexShape& trian)
{
	// Get Rectangle Points & Normals
	ConvexShapeInfo rectInfo;
	rectInfo.rectShape = &rect;
	rectInfo.ComputPointsAndNormals();

	// Get Triangle Points & Normals
	ConvexShapeInfo trianInfo;
	trianInfo.convexShape = &trian;
	trianInfo.ComputPointsAndNormals();

	// Square -> Triangle
	for (int i = 0; i < rectInfo.numPoints; i++)
	{
		if (IsPointInConvexShape(rectInfo.points[i], trianInfo.points, trianInfo.normals))
		{
			return true;
		}
	}

	// Triangle -> Square
	for (int i = 0; i < trianInfo.numPoints; i++)
	{
		if (IsPointInConvexShape(trianInfo.points[i], rectInfo.points, rectInfo.normals))
		{
			return true;
		}
	}

	return false;
}

bool CollisionManager::CheckCollisionsTriangleTriangle(const sf::ConvexShape& trian1, const sf::ConvexShape& trian2)
{
	sf::Vector2f trianPos1 = trian1.getPosition();
	sf::Vector2f trianPos2 = trian2.getPosition();

	Vec2f triangle1[3] = { {(trian1.getPoint(0) + trianPos1).x, (trian1.getPoint(0) + trianPos1).y}, {(trian1.getPoint(1) + trianPos1).x, (trian1.getPoint(1) + trianPos1).y}, {(trian1.getPoint(2) + trianPos1).x, (trian1.getPoint(2) + trianPos1).y} };
	Vec2f triangle2[3] = { {(trian2.getPoint(0) + trianPos2).x, (trian2.getPoint(0) + trianPos2).y}, {(trian2.getPoint(1) + trianPos2).x, (trian2.getPoint(1) + trianPos2).y}, {(trian2.getPoint(2) + trianPos2).x, (trian2.getPoint(2) + trianPos2).y} };

	ConvexShapeInfo trianA;
	trianA.convexShape = &trian1;
	trianA.ComputPointsAndNormals();

	ConvexShapeInfo trianB;
	trianB.convexShape = &trian2;
	trianB.ComputPointsAndNormals();

	// A -> B
	for (int i = 0; i < trianA.numPoints; i++)
	{
		if (IsPointInConvexShape(trianA.points[i], trianB.points, trianB.normals))
		{
			return true;
		}
	}

	// B -> A
	for (int i = 0; i < trianB.numPoints; i++)
	{
		if (IsPointInConvexShape(trianB.points[i], trianA.points, trianA.normals))
		{
			return true;
		}
	}

	return false;
}

bool CollisionManager::CheckCollisionsCircleRectangle(const sf::CircleShape& circle, const sf::RectangleShape& rect)
{
	ConvexShapeInfo rectInfo;
	rectInfo.rectShape = &rect;
	rectInfo.ComputPointsAndNormals();

	float cr = circle.getRadius(); // circle radius
	float cx = circle.getPosition().x; // circle x position (center)
	float cy = circle.getPosition().y; // circle y position (center)
	Vec2f centerCircle = circle.getPosition();

	if (IsPointInConvexShape(centerCircle, rectInfo.points, rectInfo.normals))
	{
		return true;
	}

	for (int i = 0; i < rectInfo.numPoints; i++)
	{
		float dist = DistancePointToSegment(centerCircle, rectInfo.points[i], rectInfo.points[(i + 1) % rectInfo.numPoints]);
		if (dist <= cr)
		{
			return true;
		}
	}

	return false;
}

bool CollisionManager::CheckCollisionsCircleTriangle(const sf::CircleShape& circle, const sf::ConvexShape& trian)
{
	ConvexShapeInfo trianInfo;
	trianInfo.convexShape = &trian;
	trianInfo.ComputPointsAndNormals();

	float cr = circle.getRadius(); // circle radius
	float cx = circle.getPosition().x; // circle x position (center)
	float cy = circle.getPosition().y; // circle y position (center)
	Vec2f centerCircle = circle.getPosition();

	if (IsPointInConvexShape(centerCircle, trianInfo.points, trianInfo.normals))
	{
		return true;
	}

	for (int i = 0; i < trianInfo.numPoints; i++)
	{
		float dist = DistancePointToSegment(centerCircle, trianInfo.points[i], trianInfo.points[(i + 1) % trianInfo.numPoints]);
		if (dist <= cr)
		{
			return true;
		}
	}

	return false;
}

bool CollisionManager::IsPointInConvexShape(const Vec2f& point, const std::vector<Vec2f>& shapePoints, const std::vector<Vec2f>& convNormals)
{
	int numPoints = shapePoints.size();
	for (int i = 0; i < numPoints; i++) 
	{
		if (convNormals[i].Dot(point - shapePoints[i]) > 0)
		{
			return false;
		}
	}
	return true;
}

float CollisionManager::DistancePointToSegment(const Vec2f& point, const Vec2f& start, const Vec2f& end)
{
	// Vecteur du segment et vecteur du point par rapport au début du segment
	Vec2f AB = end - start;
	Vec2f AP = point - start;

	// Longueur au carré du segment (évite sqrt inutile)
	float len2 = AB.Dot(AB);

	// Segment dégénéré (start == end) : distance au point start
	if (len2 == 0.0f)
	{
		float dx = point.x - start.x;
		float dy = point.y - start.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	// Paramètre de projection normalisé t = (AP·AB) / |AB|^2
	float t = AP.Dot(AB) / len2;

	// Clamp entre 0 et 1 pour rester sur le segment
	if (t < 0.0f) t = 0.0f;
	else if (t > 1.0f) t = 1.0f;

	// Point projeté sur le segment
	Vec2f projection = start + AB * t;

	// Distance entre le point et la projection
	float dx = point.x - projection.x;
	float dy = point.y - projection.y;
	return std::sqrt(dx * dx + dy * dy);
}