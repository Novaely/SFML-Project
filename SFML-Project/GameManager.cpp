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

	void GameManager::BonusVie(Player & player, float vieRegen)
	{
		player.health += vieRegen;
	}

	void GameManager::BonusTir(Player & player)
	{
		player.LevelShooter += 1;
	}