#include "GameManager.h"


GameManager::GameManager()
{
	score = 0;
	multiplicateur = 1;
	timerBonusScore = 0.0f;
	timerBonusScoreCheck = 0.0f;
}
void GameManager::Update(float deltaTime, sf::RenderWindow& window)
{
	UpdateAll(deltaTime, window);
	timerBonusScore += deltaTime;
	if (timerBonusScore > timerBonusScoreCheck)
	{
		multiplicateur = 1;
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

void GameManager::UpdateAll(float deltaTime, sf::RenderWindow& window) {
	player->Update(deltaTime, window);

	std::list<Bullet*>::iterator it = bullets.begin();
	while (it != bullets.end()) {
		(*it)->Update(deltaTime, window);
		it++;
	}
}