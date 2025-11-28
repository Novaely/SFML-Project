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
	bullets = &(gm->bullets);
	
}

void CollisionManager::Update(float deltaTime)
{
	sf::Vector2f playerPos = pShape->getPosition();

	std::list<CACEnemy*>::iterator it = (*cacEnemy).begin();
	while (it != (*cacEnemy).end()) 
	{
		sf::RectangleShape* cacEnemyShape = (sf::RectangleShape*)(*it)->shape;

		if (CheckCollisionsSquareTriangle(*cacEnemyShape, *pShape))
		{
			player->OnCollisionEnter((*it));
			(*it)->OnCollisionEnter(player);
			std::cout << "Collision between CACEnemy and Player" << std::endl;
		}
		it++;
	}

	std::list<ShooterEnemy*>::iterator it2 = (*shooterEnemy).begin();
	while (it2 != (*shooterEnemy).end())
	{
		sf::ConvexShape* shooterEnemyShape = (sf::ConvexShape*)(*it2)->shape;
		if (CheckCollisionsTriangleTriangle(*shooterEnemyShape, *pShape))
		{
			player->OnCollisionEnter((*it2));
			(*it)->OnCollisionEnter(player);
			std::cout << "Collision between ShooterEnemy and Player" << std::endl;
		}
		it2++;
	}

	std::list<Bullet*>::iterator it3 = (*bullets).begin();
	while (it3 != (*bullets).end())
	{
		sf::CircleShape* bulletShape = (sf::CircleShape*)(*it3)->shape;
		if (CheckCollisionsCircleTriangle(*bulletShape, *pShape))
		{
			player->OnCollisionEnter((*it3));
			(*it3)->OnCollisionEnter(player);
			std::cout << "Collision between Bullet and Player" << std::endl;
		}

		std::list<CACEnemy*>::iterator it4 = (*cacEnemy).begin();
		while (it4 != (*cacEnemy).end())
		{
			sf::RectangleShape* CACEnemyShape = (sf::RectangleShape*)(*it4)->shape;
			if (CheckCollisionsCircleSquare(*bulletShape, *CACEnemyShape))
			{
				(*it4)->OnCollisionEnter((*it3));
				(*it3)->OnCollisionEnter((*it4));
				std::cout << "Collision between Bullet and CACEnemy" << std::endl;
			}
			it4++;
		}

		std::list<ShooterEnemy*>::iterator it5 = (*shooterEnemy).begin();
		while (it5 != (*shooterEnemy).end())
		{
			sf::ConvexShape* ShooterEnemyShape = (sf::ConvexShape*)(*it5)->shape;
			if (CheckCollisionsCircleTriangle(*bulletShape, *ShooterEnemyShape))
			{
				(*it5)->OnCollisionEnter((*it3));
				(*it3)->OnCollisionEnter((*it5));
				std::cout << "Collision between Bullet and ShooterEnemy" << std::endl;
			}
			it5++;
		}

		if(!CheckCollisionsCircleSquare(*bulletShape, *(sf::RectangleShape*)windowShape))
		{

			std::cout << "Collision between Bullet and Window Bounds" << std::endl;
		}

		it3++;
	}

}

bool CollisionManager::CheckCollisionsSquareTriangle(sf::RectangleShape rect, sf::ConvexShape trian)
{
	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f p1 = rect.getPoint(0) + rectPos;
	sf::Vector2f p2 = rect.getPoint(1) + rectPos;
	sf::Vector2f p3 = rect.getPoint(2) + rectPos;
	sf::Vector2f p4 = rect.getPoint(3) + rectPos;
	vector2f square[4] = { (p1.x, p1.y), (p2.x, p2.y), (p3.x, p3.y), (p4.x, p4.y) };
	

	sf::Vector2f trianPos = trian.getPosition();
	vector2f triangle[3] = { {(trian.getPoint(0) + trianPos).x, (trian.getPoint(0) + trianPos).y}, {(trian.getPoint(1) + trianPos).x, (trian.getPoint(1) + trianPos).y}, {(trian.getPoint(2) + trianPos).x, (trian.getPoint(2) + trianPos).y} };


	float rw = square[1].x - square[0].x; // width
	float rh = square[3].y - square[0].y; // height
	float rx = square[0].x; // x position
	float ry = square[0].y; // y position

	// Triangle -> Square
	for (int i = 0; i < 3; i++)
	{
		if ((triangle[i].y >= ry && triangle[i].y <= rh + ry) && (triangle[i].x >= rx && triangle[i].x <= rw + rx))
		{
			std::cout << "Collision detected" << std::endl;
			return true;
		}
	}

	// Square -> Triangle
	for (int i = 0; i < 4; i++)
	{

        if (IsPointInTriangle(square[i], triangle))
        {
			std::cout << "Collision detected" << std::endl;
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
			std::cout << "Collision detected" << std::endl;
			return true;
		}
		if (IsPointInTriangle(triangle2[i], triangle1))
		{
			std::cout << "Collision detected" << std::endl;
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
		std::cout << "Collision detected" << std::endl;
		return true;
	}
	return false;

	//if (((cx - cr >= rx && cx + cr <= rw + rx) && (cy - cr >= ry && cy + cr <= ry + rh)) || (cx - cr < rx && cx + cr > rw + rx) && (cy - cr < ry && cy + cr > ry + rh))
	//{
	//	return false;
	//}
	//std::cout << "Collision detected" << std::endl;
	//return true;
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
		std::cout << "Collision detected" << std::endl;
		return true;
	}


	for (int i = 0; i < 3; i++)
	{
		float dist = DistancePointToSegment((cx, cy), triangle[i], triangle[(i + 1) % 3]);
		if (dist <= cr)
		{
			std::cout << "Collision detected" << std::endl;
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

	if (ABP.Dot(n1) > 0)
	{
		return false;
	}
	if (BCP.Dot(n2) > 0)
	{
		return false;
	}
	if (CAP.Dot(n3) > 0)
	{
		return false;
	}
	return true;
}