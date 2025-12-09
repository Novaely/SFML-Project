#include "CollisionManager.h"

CollisionManager::CollisionManager(GameManager* gm, CustomVector2f windowSize)
{
	windowShape = new sf::RectangleShape();
	((sf::RectangleShape*)windowShape)->setSize({ windowSize.x, windowSize.y});
	
	gameManager = gm;
	player = gm->player;
	pShape = (sf::ConvexShape*)player->shape;
	cacEnemy = &(gm->cacEnemy);
	shooterEnemy = &(gm->shooterEnemy);
	turretEnemy = &(gm->turretEnemy);
	collectibles = &(gm->collectibles);
	bullets = &(gm->bullets);
	lightnings = &(gm->lightnings);
}

void CollisionManager::Update(float deltaTime)
{
	sf::Vector2f playerPos = pShape->getPosition();

	// CACEnemy with Player
	std::list<CACEnemy*>::iterator cacEnemyIt = (*cacEnemy).begin();
	while (cacEnemyIt != (*cacEnemy).end()) 
	{
		if (!(*cacEnemyIt)->isAlive) {
			cacEnemyIt++;
			continue;
		}

		sf::RectangleShape* cacEnemyShape = (sf::RectangleShape*)(*cacEnemyIt)->shape;

		if (CheckCollisionsSquareTriangle(*cacEnemyShape, *pShape))
		{
			player->OnCollisionEnter((*cacEnemyIt));
			(*cacEnemyIt)->OnCollisionEnter(player);
		}
		cacEnemyIt++;
	}

	// ShooterEnemy with Player
	std::list<ShooterEnemy*>::iterator shooterEnemyIt = (*shooterEnemy).begin();
	while (shooterEnemyIt != (*shooterEnemy).end())
	{
		if (!(*shooterEnemyIt)->isAlive) {
			shooterEnemyIt++;
			continue;
		}

		sf::ConvexShape* shooterEnemyShape = (sf::ConvexShape*)(*shooterEnemyIt)->shape;
		if (CheckCollisionsTriangleTriangle(*shooterEnemyShape, *pShape))
		{
			player->OnCollisionEnter((*shooterEnemyIt));
			(*shooterEnemyIt)->OnCollisionEnter(player);
		}
		shooterEnemyIt++;
	}

	// TurretEnemy with Player
	std::list<TurretEnemy*>::iterator turretEnemyIt = (*turretEnemy).begin();
	while (turretEnemyIt != (*turretEnemy).end())
	{
		if (!(*turretEnemyIt)->isAlive) {
			turretEnemyIt++;
			continue;
		}

		sf::ConvexShape* turretEnemyShape = (sf::ConvexShape*)(*turretEnemyIt)->shape;
		if (CheckCollisionsTriangleTriangle(*turretEnemyShape, *pShape))
		{
			player->OnCollisionEnter((*turretEnemyIt));
			(*turretEnemyIt)->OnCollisionEnter(player);
		}
		turretEnemyIt++;
	}

	// Lightning with Player
	auto lightningIt = (*lightnings).begin();
	while (lightningIt != (*lightnings).end())
	{
		sf::RectangleShape* lightningShape = (sf::RectangleShape*)(*lightningIt)->shape;
		//std::cout << "New it" << std::endl;
		//std::cout << (lightningShape->getPoint(0) + lightningShape->getPosition()).x << " Y: " << (lightningShape->getPoint(0) + lightningShape->getPosition()).y << std::endl;
		//std::cout << (lightningShape->getPoint(1) + lightningShape->getPosition()).x << " Y: " << (lightningShape->getPoint(1) + lightningShape->getPosition()).y << std::endl;
		//std::cout << (lightningShape->getPoint(2) + lightningShape->getPosition()).x << " Y: " << (lightningShape->getPoint(2) + lightningShape->getPosition()).y << std::endl;
		//std::cout << (lightningShape->getPoint(3) + lightningShape->getPosition()).x << " Y: " << (lightningShape->getPoint(3) + lightningShape->getPosition()).y << std::endl;
		//std::cout << lightningShape->getOrigin().x << " Y:" << lightningShape->getOrigin().y << std::endl;

		Vec2f pos = lightningShape->getPosition();
		Vec2f p0 = Math::RotatePoint(lightningShape->getPoint(0), Vec2f::zero, Math::ToRad(lightningShape->getRotation())) + pos;
		Vec2f p1 = Math::RotatePoint(lightningShape->getPoint(1), Vec2f::zero, Math::ToRad(lightningShape->getRotation())) + pos;
		Vec2f p2 = Math::RotatePoint(lightningShape->getPoint(2), Vec2f::zero, Math::ToRad(lightningShape->getRotation())) + pos;
		Vec2f p3 = Math::RotatePoint(lightningShape->getPoint(3), Vec2f::zero, Math::ToRad(lightningShape->getRotation())) + pos;

		//std::cout << "X: " << p0.x << " Y: " << p0.y << std::endl;
		//std::cout << "X: " << p1.x << " Y: " << p1.y << std::endl;
		//std::cout << "X: " << p2.x << " Y: " << p2.y << std::endl;
		//std::cout << "X: " << p3.x << " Y: " << p3.y << std::endl;

		if (CheckCollisionsSquareTriangle(*lightningShape, *pShape))
		{
			player->OnCollisionEnter((*lightningIt));
			(*lightningIt)->OnCollisionEnter(player);
		}
		lightningIt++;
	}

	// Others with Bullets
	std::list<Bullet*>::iterator bulletIt = (*bullets).begin();
	while (bulletIt != (*bullets).end())
	{
		if (!(*bulletIt)->isAlive) {
			bulletIt++;
			continue;
		}

		// With player
		sf::CircleShape* bulletShape = (sf::CircleShape*)(*bulletIt)->shape;
		if (CheckCollisionsCircleTriangle(*bulletShape, *pShape))
		{
			player->OnCollisionEnter((*bulletIt));
			(*bulletIt)->OnCollisionEnter(player);
		}

		// With CacEnemy
		std::list<CACEnemy*>::iterator cacEnemyBulletsIt = (*cacEnemy).begin();
		while (cacEnemyBulletsIt != (*cacEnemy).end())
		{
			if (!(*cacEnemyBulletsIt)->isAlive) {
				cacEnemyBulletsIt++;
				continue;
			}

			sf::RectangleShape* CACEnemyShape = (sf::RectangleShape*)(*cacEnemyBulletsIt)->shape;
			if (CheckCollisionsCircleSquare(*bulletShape, *CACEnemyShape))
			{
				(*cacEnemyBulletsIt)->OnCollisionEnter((*bulletIt));
				(*bulletIt)->OnCollisionEnter((*cacEnemyBulletsIt));
			}
			cacEnemyBulletsIt++;
		}

		std::list<ShooterEnemy*>::iterator shooterEnemyBulletsIt = (*shooterEnemy).begin();
		while (shooterEnemyBulletsIt != (*shooterEnemy).end())
		{
			if (!(*shooterEnemyBulletsIt)->isAlive) {
				shooterEnemyBulletsIt++;
				continue;
			}

			sf::ConvexShape* ShooterEnemyShape = (sf::ConvexShape*)(*shooterEnemyBulletsIt)->shape;
			if (CheckCollisionsCircleTriangle(*bulletShape, *ShooterEnemyShape))
			{
				(*shooterEnemyBulletsIt)->OnCollisionEnter((*bulletIt));
				(*bulletIt)->OnCollisionEnter((*shooterEnemyBulletsIt));
			}
			shooterEnemyBulletsIt++;
		}

		// With TurretEnemy
		std::list<TurretEnemy*>::iterator turretEnemyBulletsIt = (*turretEnemy).begin();
		while (turretEnemyBulletsIt != (*turretEnemy).end())
		{
			if (!(*turretEnemyBulletsIt)->isAlive) {
				turretEnemyBulletsIt++;
				continue;
			}

			sf::ConvexShape* turretEnemyShape = (sf::ConvexShape*)(*turretEnemyBulletsIt)->shape;
			if (CheckCollisionsCircleTriangle(*bulletShape, *turretEnemyShape))
			{
				(*turretEnemyBulletsIt)->OnCollisionEnter((*bulletIt));
				(*bulletIt)->OnCollisionEnter((*turretEnemyBulletsIt));
			}
			turretEnemyBulletsIt++;
		}

		if(!CheckCollisionsCircleSquare(*bulletShape, *(sf::RectangleShape*)windowShape))
		{
			(*bulletIt)->OnCollisionEnter(nullptr);
		}
		bulletIt++;
	}

	// Collectibles with Player
	std::list<Collectible*>::iterator collectibleIt = (*collectibles).begin();
	while (collectibleIt != (*collectibles).end())
	{
		if (!(*collectibleIt)->isAlive) {
			collectibleIt++;
			continue;
		}

		sf::CircleShape* collectibles = (sf::CircleShape*)(*collectibleIt)->shape;

		if (CheckCollisionsCircleTriangle(*collectibles, *pShape))
		{
			player->OnCollisionEnter((*collectibleIt));
			(*collectibleIt)->OnCollisionEnter(player);
		}
		collectibleIt++;
	}
}

bool CollisionManager::IsPointInConvexShape(const Vec2f& point, Vec2f shapePoints[], Vec2f convNormals[], int numNormals)
{
	Vec2f vecToPoint;
	for (int i = 0; i < numNormals; i++) 
	{
		vecToPoint = point - shapePoints[i];
		if (vecToPoint.Dot(convNormals[i]) > 0)
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

	Vec2f rectP1 = Math::RotatePoint(rect.getPoint(0), Vec2f::zero, rectRotation) + rectPos;
	Vec2f rectP2 = Math::RotatePoint(rect.getPoint(1), Vec2f::zero, rectRotation) + rectPos;
	Vec2f rectP3 = Math::RotatePoint(rect.getPoint(2), Vec2f::zero, rectRotation) + rectPos;
	Vec2f rectP4 = Math::RotatePoint(rect.getPoint(3), Vec2f::zero, rectRotation) + rectPos;

	Vec2f rectS1Normal = (rectP2 - rectP1).GetNormalClockWise();
	Vec2f rectS2Normal = (rectP3 - rectP2).GetNormalClockWise();
	Vec2f rectS3Normal = (rectP4 - rectP3).GetNormalClockWise();
	Vec2f rectS4Normal = (rectP1 - rectP4).GetNormalClockWise();

	Vec2f squarePoints[4] = { rectP1, rectP2, rectP3, rectP4 };
	Vec2f squareSidesNormals[4] = { rectS1Normal, rectS2Normal, rectS3Normal, rectS4Normal };

	// Get Triangle Points
	Vec2f trianPos = trian.getPosition();
	float trianRotation = Math::ToRad(trian.getRotation());

	Vec2f trianP1 = Math::RotatePoint(trian.getPoint(0), Vec2f::zero, trianRotation) + trianPos;
	Vec2f trianP2 = Math::RotatePoint(trian.getPoint(1), Vec2f::zero, trianRotation) + trianPos;
	Vec2f trianP3 = Math::RotatePoint(trian.getPoint(2), Vec2f::zero, trianRotation) + trianPos;

	Vec2f trianS1Normal = (trianP2 - trianP1).GetNormalClockWise();
	Vec2f trianS2Normal = (trianP3 - trianP2).GetNormalClockWise();
	Vec2f trianS3Normal = (trianP1 - trianP3).GetNormalClockWise();

	Vec2f trianglePoints[3] = {trianP1, trianP2, trianP3};
	Vec2f triangleSidesNormals[3] = { trianS1Normal , trianS2Normal, trianS3Normal };

	// Square -> Triangle
	for (int i = 0; i < 4; i++)
	{
		if (IsPointInConvexShape(squarePoints[i], trianglePoints, triangleSidesNormals, 3))
		{
			return true;
		}
	}

	// Triangle -> Square
	for (int i = 0; i < 3; i++)
	{
		if (IsPointInConvexShape(trianglePoints[i], squarePoints, squareSidesNormals, 4))
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

bool CollisionManager::CheckCollisionsCircleSquare(const sf::CircleShape& circle, const sf::RectangleShape& rect)
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