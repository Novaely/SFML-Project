#include "GameManager.h"


GameManager::GameManager()
{
	_score = 0;
	_multiplicateur = 1;
	_timerBonusScore = 0.0f;
	_timerBonusScoreCheck = 0.0f;


}
	void GameManager::Update(float deltaTime)
	{
		_timerBonusScore += deltaTime;
		if (_timerBonusScore > _timerBonusScoreCheck)
		{
			_multiplicateur = 1;
		}
	}


	void GameManager::BonusScore(float timer, int multiplicateur)
	{
		_multiplicateur = multiplicateur;
		_timerBonusScore = 0;
		_timerBonusScoreCheck = timer;

	}

	void GameManager::BonusVie(Player & player, float vieRegen)
	{
		player.health += vieRegen;
	}

	void GameManager::BonusTir(Player & player)
	{
		player.LevelShooter += 1;
	}