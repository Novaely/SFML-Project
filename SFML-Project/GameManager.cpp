#include "GameManager.h"

GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::GetInstance()
{
	return _instance;
}

GameManager::~GameManager()
{
	if (_instance == this)
	{
		_instance = nullptr;
	}
}

GameManager::GameManager()
{
	if (_instance == nullptr)
	{
		_instance = this;
	}
	else
	{
		std::cout << "GameManager already exist !" << std::endl;
		delete this;
		return;
	}

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

void GameManager::PlayerShoot()
{
	if (!player->CanShoot()) return;

	player->Shoot();
	CustomVector2f bulletSpawnLocalPos = Math::RotatePoint(player->bulletSpawnPos, CustomVector2f::zero, Math::ToRad(player->rotation));
	CustomVector2f pos = player->position + bulletSpawnLocalPos;

	CreateBullet(Team::Player, pos, player->speedBullet, player->GetLookDirection(), 10);
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