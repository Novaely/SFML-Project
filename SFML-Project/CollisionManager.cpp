#include "CollisionManager.h"

CollisionManager::CollisionManager(GameManager* gm, CustomVector2f windowSize)
{
	windowShape = new sf::RectangleShape();
	((sf::RectangleShape*)windowShape)->setSize({ windowSize.x, windowSize.y});
	
	gameManager = gm;

	gameObjects = &(gm->gameObjects);
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
	return (static_cast<LayerMask>(goA->layer) & goB->collisionMask) && (static_cast<LayerMask>(goB->layer) & goA->collisionMask);
}

bool CollisionManager::AreInDistance(GameObject* goA, GameObject* goB)
{
	return (goA->broadRadius + goB->broadRadius) * (goA->broadRadius + goB->broadRadius) >= (goA->position - goB->position).GetSquaredMagnitude();
}

void CollisionManager::Update(float deltaTime)
{
	auto itGoA = (*gameObjects).begin();
	std::list<GameObject*>::iterator itGoB;
	while (itGoA != (*gameObjects).end())
	{
		itGoB = std::next(itGoA);
		while (itGoB != (*gameObjects).end())
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

bool CollisionManager::CheckCollisionsSquareTriangle(const sf::RectangleShape& rect, const sf::ConvexShape& trian)
{
	// Get Rectangle Points & Normals
	Vec2f rectPos = rect.getPosition();
	float rectRotation = Math::ToRad(rect.getRotation());

	int rectNumPoints = rect.getPointCount();
	std::vector<Vec2f> rectPoints(rectNumPoints, Vec2f::zero);
	std::vector<Vec2f> rectNormals(rectNumPoints, Vec2f::zero);

	for (int i = 0; i < rectNumPoints; i++)
	{
		rectPoints[i] = Math::RotatePoint(rect.getPoint(i), Vec2f::zero, rectRotation) + rectPos;
	}

	int rectNextIndex;
	for (int i = 0; i < rectNumPoints; i++)
	{
		rectNextIndex = (i + 1) % rectNumPoints;
		rectNormals[i] = (rectPoints[rectNextIndex] - rectPoints[i]).GetNormalClockWise().GetNormalised();
	}

	// Get Triangle Points & Normals
	Vec2f trianPos = trian.getPosition();
	float trianRotation = Math::ToRad(trian.getRotation());

	int trianNumPoints = trian.getPointCount();
	std::vector<Vec2f> trianPoints(trianNumPoints, Vec2f::zero);
	std::vector<Vec2f> trianNormals(trianNumPoints, Vec2f::zero);

	for (int i = 0; i < trianNumPoints; i++)
	{
		trianPoints[i] = Math::RotatePoint(trian.getPoint(i), Vec2f::zero, trianRotation) + trianPos;
	}

	int trianNextIndex;
	for (int i = 0; i < trianNumPoints; i++)
	{
		trianNextIndex = (i + 1) % trianNumPoints;
		trianNormals[i] = (trianPoints[trianNextIndex] - trianPoints[i]).GetNormalClockWise().GetNormalised();
	}

	// Square -> Triangle
	for (int i = 0; i < rectNumPoints; i++)
	{
		if (IsPointInConvexShape(rectPoints[i], trianPoints, trianNormals))
		{
			return true;
		}
	}

	// Triangle -> Square
	for (int i = 0; i < trianNumPoints; i++)
	{
		if (IsPointInConvexShape(trianPoints[i], rectPoints, rectNormals))
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


	for (int i = 0; i < 3; i++)
	{
		if (IsPointInTriangle(triangle1[i], triangle2))
		{
			return true;
		}
		if (IsPointInTriangle(triangle2[i], triangle1))
		{
			return true;
		}
	}
	return false;
}

bool CollisionManager::CheckCollisionsCircleRectangle(const sf::CircleShape& circle, const sf::RectangleShape& rect)
{
	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f p1 = rect.getPoint(0) + rectPos;
	sf::Vector2f p2 = rect.getPoint(1) + rectPos;
	sf::Vector2f p3 = rect.getPoint(2) + rectPos;
	sf::Vector2f p4 = rect.getPoint(3) + rectPos;
	Vec2f square[4] = { {p1.x, p1.y}, {p2.x, p2.y}, {p3.x, p3.y}, {p4.x, p4.y} };

	float rw = square[1].x - square[0].x; // width
	float rh = square[3].y - square[0].y; // height
	float rx = square[0].x; // x position
	float ry = square[0].y; // y position

	float cr = circle.getRadius(); // circle radius
	float cx = circle.getPosition().x; // circle x position (center)
	float cy = circle.getPosition().y; // circle y position (center)

	// Trouve le point du rectangle le plus proche du centre du cercle
	float closestX = cx;
	if (closestX < rx) closestX = rx;
	else if (closestX > rx + rw) closestX = rx + rw;

	float closestY = cy;
	if (closestY < ry) closestY = ry;
	else if (closestY > ry + rh) closestY = ry + rh;

	// Distance au carré entre le centre et ce point le plus proche
	float dx = cx - closestX;
	float dy = cy - closestY;

	if (dx * dx + dy * dy <= cr * cr)
	{
		return true;
	}
	return false;
}

bool CollisionManager::CheckCollisionsCircleTriangle(const sf::CircleShape& circle, const sf::ConvexShape& trian)
{
	sf::Vector2f trianPos = trian.getPosition();

	Vec2f triangle[3] = { {(trian.getPoint(0) + trianPos).x, (trian.getPoint(0) + trianPos).y},  {(trian.getPoint(1) + trianPos).x, (trian.getPoint(1) + trianPos).y}, {(trian.getPoint(2) + trianPos).x, (trian.getPoint(2) + trianPos).y} };

	float cr = circle.getRadius(); // circle radius
	float cx = circle.getPosition().x; // circle x position (center)
	float cy = circle.getPosition().y; // circle y position (center)
	Vec2f centerCircle = { circle.getPosition().x, circle.getPosition().y };

	if (IsPointInTriangle(centerCircle, triangle))
	{
		return true;
	}


	for (int i = 0; i < 3; i++)
	{
		float dist = DistancePointToSegment(centerCircle, triangle[i], triangle[(i + 1) % 3]);
		if (dist <= cr)
		{
			return true;
		}
	}

	return false;
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


bool CollisionManager::IsPointInTriangle(const Vec2f& point, Vec2f triangle[3])
{
	Vec2f AB = triangle[1] - triangle[0];
	Vec2f BC = triangle[2] - triangle[1];
	Vec2f CA = triangle[0] - triangle[2];

	Vec2f ABP = point - triangle[0] + AB * 0.5f;
	Vec2f BCP = point - triangle[1] + BC * 0.5f;
	Vec2f CAP = point - triangle[2] + CA * 0.5f;

	Vec2f n1 = Vec2f(-AB.y, AB.x);
	Vec2f n2 = Vec2f(-BC.y, BC.x);
	Vec2f n3 = Vec2f(-CA.y, CA.x);

	if (dotProduct(ABP.x, ABP.y, n1.x, n1.y) < 0)
	{
		return false;
	}
	if (dotProduct(BCP.x, BCP.y, n2.x, n2.y) < 0)
	{
		return false;
	}
	if (dotProduct(CAP.x, CAP.y, n3.x, n3.y) < 0)
	{
		return false;
	}
	return true;
}

float CollisionManager::dotProduct(float vx1, float vy1, float vx2, float vy2)
{
	return vx1 * vx2 + vy1 * vy2;
}