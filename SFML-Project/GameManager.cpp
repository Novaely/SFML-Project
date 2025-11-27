#include "GameManager.h"


GameManager::GameManager()
{
	score = 0;
	multiplicateur = 1;
	timerBonusScore = 0.0f;
	timerBonusScoreCheck = 0.0f;
}
void GameManager::Update(float deltaTime)
{
	UpdateAll(deltaTime);
	timerBonusScore += deltaTime;
	if (timerBonusScore > timerBonusScoreCheck)
	{
		multiplicateur = 1;
	}
}

void GameManager::Draw(sf::RenderWindow& window)
{
	player->Draw(window);

	std::list<Bullet*>::iterator it = bullets.begin();
	while (it != bullets.end()) {
		(*it)->Draw(window);
		it++;
	}

	std::list<CACEnemy*>::iterator cacIt = cacEnemy.begin();
	while (cacIt != cacEnemy.end())
	{
		(*cacIt)->Draw(window);
		cacIt++;
	}

	std::list<ShooterEnemy*>::iterator shooterIt = shooterEnemy.begin();
	while (shooterIt != shooterEnemy.end())
	{
		(*shooterIt)->Draw(window);
		shooterIt++;
	}
}

void GameManager::BonusScore(float timer, int multiplicateur)
{
	multiplicateur = multiplicateur;
	timerBonusScore = 0;
	timerBonusScoreCheck = timer;

}

void GameManager::BonusVie(float vieRegen)
{
	(*player).health += vieRegen;
}

void GameManager::BonusTir()
{
	(*player).LevelShooter += 1;
}

void GameManager::CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage)
{
	bullets.push_back(poolManager->GetBullet(team,position,speed,direction,damage));
}

void GameManager::UpdateAll(float deltaTime) {
	player->Update(deltaTime);

	std::list<Bullet*>::iterator it = bullets.begin();
	while (it != bullets.end()) {
		(*it)->Update(deltaTime);
		it++;
	}

	std::list<CACEnemy*>::iterator cacIt = cacEnemy.begin();
	while (cacIt != cacEnemy.end())
	{
		(*cacIt)->Update(deltaTime);
		cacIt++;
	}

	std::list<ShooterEnemy*>::iterator shooterIt = shooterEnemy.begin();
	while (shooterIt != shooterEnemy.end())
	{
		(*shooterIt)->Update(deltaTime);
		shooterIt++;
	}
}