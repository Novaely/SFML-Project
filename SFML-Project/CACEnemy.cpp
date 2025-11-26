#include "CACEnemy.h"

CACEnemy::CACEnemy() : Enemy()
{
	detectionRadius = 150.0f;
	attackRadius = 50.0f;
	timeBetweenAttacks = 1.0f;
	attackTimer = 0.0f;
	damage = 10.0f;
}

void CACEnemy::Active()
{
}

void CACEnemy::Desactive()
{
}

void CACEnemy::Update(float deltaTime, sf::RenderWindow& window)
{
	
}