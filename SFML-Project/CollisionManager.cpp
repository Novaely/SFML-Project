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
	
}

void CollisionManager::Update(float deltaTime)
{
	sf::Vector2f playerPos = pShape->getPosition();

	// CACEnemy with Player
	std::list<CACEnemy*>::iterator cacEnemyIt = (*cacEnemy).begin();
	while (cacEnemyIt != (*cacEnemy).end()) 
	{
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
		sf::ConvexShape* turretEnemyShape = (sf::ConvexShape*)(*turretEnemyIt)->shape;
		if (CheckCollisionsTriangleTriangle(*turretEnemyShape, *pShape))
		{
			player->OnCollisionEnter((*turretEnemyIt));
			(*turretEnemyIt)->OnCollisionEnter(player);
		}
		turretEnemyIt++;
	}

	// Others with Bullets
	std::list<Bullet*>::iterator bulletIt = (*bullets).begin();
	while (bulletIt != (*bullets).end())
	{
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
		sf::CircleShape* collectibles = (sf::CircleShape*)(*collectibleIt)->shape;

		if (CheckCollisionsCircleTriangle(*collectibles, *pShape))
		{
			player->OnCollisionEnter((*collectibleIt));
			(*collectibleIt)->OnCollisionEnter(player);
		}
		collectibleIt++;
	}
}

bool CollisionManager::CheckCollisionsSquareTriangle(sf::RectangleShape rect, sf::ConvexShape trian)
{
	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f p1 = rect.getPoint(0) + rectPos;
	sf::Vector2f p2 = rect.getPoint(1) + rectPos;
	sf::Vector2f p3 = rect.getPoint(2) + rectPos;
	sf::Vector2f p4 = rect.getPoint(3) + rectPos;
	vector2f square[4] = { {p1.x, p1.y}, {p2.x, p2.y}, {p3.x, p3.y}, {p4.x, p4.y} };

	

	sf::Vector2f trianPos = trian.getPosition();
	vector2f triangle[3] = { {(trian.getPoint(0) + trianPos).x, (trian.getPoint(0) + trianPos).y}, {(trian.getPoint(1) + trianPos).x, (trian.getPoint(1) + trianPos).y}, {(trian.getPoint(2) + trianPos).x, (trian.getPoint(2) + trianPos).y} };


	float rw = square[1].x - square[0].x; // width
	float rh = square[3].y - square[0].y; // height
	float rx = square[0].x; // x position
	float ry = square[0].y; // y position

	// Square -> Triangle
	for (int i = 0; i < 4; i++)
	{

        if (IsPointInTriangle(square[i], triangle))
        {
			return true;
        }
	}

	// Triangle -> Square
	for (int i = 0; i < 3; i++)
	{
		if ((triangle[i].y >= ry && triangle[i].y <= rh + ry) && (triangle[i].x >= rx && triangle[i].x <= rw + rx))
		{
			return true;
		}
	}

	return false;
}
bool CollisionManager::CheckCollisionsTriangleTriangle(sf::ConvexShape trian1, sf::ConvexShape trian2)
{
	sf::Vector2f trianPos1 = trian1.getPosition();
	sf::Vector2f trianPos2 = trian2.getPosition();

	vector2f triangle1[3] = { {(trian1.getPoint(0) + trianPos1).x, (trian1.getPoint(0) + trianPos1).y}, {(trian1.getPoint(1) + trianPos1).x, (trian1.getPoint(1) + trianPos1).y}, {(trian1.getPoint(2) + trianPos1).x, (trian1.getPoint(2) + trianPos1).y} };
	vector2f triangle2[3] = { {(trian2.getPoint(0) + trianPos2).x, (trian2.getPoint(0) + trianPos2).y}, {(trian2.getPoint(1) + trianPos2).x, (trian2.getPoint(1) + trianPos2).y}, {(trian2.getPoint(2) + trianPos2).x, (trian2.getPoint(2) + trianPos2).y} };


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

bool CollisionManager::CheckCollisionsCircleSquare(sf::CircleShape circle, sf::RectangleShape rect)
{
	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f p1 = rect.getPoint(0) + rectPos;
	sf::Vector2f p2 = rect.getPoint(1) + rectPos;
	sf::Vector2f p3 = rect.getPoint(2) + rectPos;
	sf::Vector2f p4 = rect.getPoint(3) + rectPos;
	vector2f square[4] = { {p1.x, p1.y}, {p2.x, p2.y}, {p3.x, p3.y}, {p4.x, p4.y} };

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

bool CollisionManager::CheckCollisionsCircleTriangle(sf::CircleShape& circle, sf::ConvexShape& trian)
{
	sf::Vector2f trianPos = trian.getPosition();

	vector2f triangle[3] = { {(trian.getPoint(0) + trianPos).x, (trian.getPoint(0) + trianPos).y},  {(trian.getPoint(1) + trianPos).x, (trian.getPoint(1) + trianPos).y}, {(trian.getPoint(2) + trianPos).x, (trian.getPoint(2) + trianPos).y} };

	float cr = circle.getRadius(); // circle radius
	float cx = circle.getPosition().x; // circle x position (center)
	float cy = circle.getPosition().y; // circle y position (center)
	vector2f centerCircle = { circle.getPosition().x, circle.getPosition().y };

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




float CollisionManager::DistancePointToSegment(vector2f point, vector2f start, vector2f end)
{
	// Vecteur du segment et vecteur du point par rapport au début du segment
	vector2f AB = end - start;
	vector2f AP = point - start;

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
	vector2f projection = start + AB * t;

	// Distance entre le point et la projection
	float dx = point.x - projection.x;
	float dy = point.y - projection.y;
	return std::sqrt(dx * dx + dy * dy);
}


bool CollisionManager::IsPointInTriangle(vector2f point, vector2f triangle[3])
{
	vector2f AB = triangle[1] - triangle[0];
	vector2f BC = triangle[2] - triangle[1];
	vector2f CA = triangle[0] - triangle[2];

	vector2f ABP = point - triangle[0] + AB * 0.5f;
	vector2f BCP = point - triangle[1] + BC * 0.5f;
	vector2f CAP = point - triangle[2] + CA * 0.5f;

	vector2f n1 = vector2f(-AB.y, AB.x);
	vector2f n2 = vector2f(-BC.y, BC.x);
	vector2f n3 = vector2f(-CA.y, CA.x);

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