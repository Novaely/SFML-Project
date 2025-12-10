#include "GameManager.h"
#include "Utils.h"

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

	if (_idGameObjectCreateListener != -1)
	{
		GameObject::RemoveCreateListener(_idGameObjectCreateListener);
		_idGameObjectCreateListener = -1;
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
	_scoreUpdate = 1;
	_multiplicateur = 1;
	_timerBonusScore = 0.0f;
	_timerBonusScoreCheck = 0.0f;
	_timerSpawnEnemies = 5;
	_chronoSpawnEnemies = _timerSpawnEnemies;
	_wantSpawnEnemy = true; //mettre en true si vous voulez avoir le spawn des ennemies
	_idGameObjectCreateListener = GameObject::AddCreateListener([this](GameObject* go)
		{
			NewGameObjectCreated(go);
		});
}

void GameManager::NewGameObjectCreated(GameObject* go)
{
	_gameObjects.push_back(go);
}

void GameManager::Update(float deltaTime, CustomVector2f windowSize)
{
	_time += deltaTime;

	if (_wantSpawnEnemy) {
		if (_chronoSpawnEnemies <= _timerSpawnEnemies) {
			_chronoSpawnEnemies += deltaTime;
		}
		else {
			_chronoSpawnEnemies = 0;
			SpawnEnemy(windowSize);
		}
	}
	UpdateAll(deltaTime);
	_timerBonusScore += deltaTime;
	if (_timerBonusScore > _timerBonusScoreCheck)
	{
		_multiplicateur = 1;
	}
}

void GameManager::Draw(sf::RenderWindow& window)
{
	auto goIt = _gameObjects.begin();
	while (goIt != _gameObjects.end()) 
	{
		(*goIt)->Draw(window);
		goIt++;
	}
}

//fonction bonus
void GameManager::BonusScore(float timer, int multiplicateur)
{
	std::cout << "Bonus Score x" << multiplicateur << " for " << timer << " seconds." << std::endl;
	_multiplicateur = multiplicateur;
	_timerBonusScore = 0;
	_timerBonusScoreCheck = timer;
}

void GameManager::BonusVie(float vieRegen)
{
	std::cout << "Bonus Vie +" << vieRegen << std::endl;
	(*player).health += vieRegen;
	if ((*player).health > 3)
	{
		(*player).health = 3;
	}
}

void GameManager::BonusTir()
{	
	std::cout << "Bonus Tir Level +" << 1 << std::endl;
	(*player).LevelShooter += 1;
}

//fonction Creatation
void GameManager::CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType)
{
	Bullet* bullet = poolManager->GetBullet(team, position, speed, direction, damage, colorType);
	bullet->isAlive = true;
	bullet->pDie = [this](GameObject* go) { this->DestroyBullet(go); };
	bullets.push_back(bullet);
	//_gameObjects.push_back(bullet);
}

void GameManager::CreateLightning(Team team, CustomVector2f position, CustomVector2f direction, float damage)
{
	LightningNode* lightning = new LightningNode();
	lightning->isAlive = true;
	lightning->damages = damage;
	lightning->team = team;
	lightning->startPoint = position;
	lightning->endPoint = position + direction * 1000;
	lightnings.push_back(lightning);

	lightning->pDie = [this](GameObject* go) { this->DestroyLightning(go); };

	lightning->StartLightning();
	lightning->Active();
	//_gameObjects.push_back(lightning);
}

void GameManager::CreateCollectible(CustomVector2f position) {
	Collectible* collectible = new Collectible();
	collectible->Color = ColorType::Yellow;
	collectible->position = position;
	collectible->isAlive = true;
	collectible->pDie = [this](GameObject* go) { this->DestroyCollectible(go); };
	switch (RandomInt(0, 2)) {
		case 0:
			collectible->pCollected = [this](GameObject* go) { this->BonusScore(5,2); }; 
			break;
		case 1:
			collectible->pCollected = [this](GameObject* go) { this->BonusVie(1); }; 
			break;
		case 2:
			collectible->pCollected = [this](GameObject* go) { this->BonusTir(); };
			break;
	}
	collectibles.push_back(collectible);
	//_gameObjects.push_back(collectible);
}

void GameManager::CreateCacEnemy(CustomVector2f position, float health,ColorType color) {

	CACEnemy* enemy = (poolManager->GetCACEnemy(position, health, player));
	enemy->isAlive = true;
	enemy->pDie = [this](GameObject* go) { this->DestroyCacEnemy(go); };
	(*enemy).Color = color;
	cacEnemy.push_back(enemy);
	//_gameObjects.push_back(enemy);
}

void GameManager::CreateShooterEnemy(CustomVector2f position, float health, ColorType color) {
	ShooterEnemy* enemy = poolManager->GetShooterEnemy(position, health, player);
	enemy->isAlive = true;
	enemy->pDie = [this](GameObject* go) { this->DestroyShooterEnemy(go); };
	(*enemy).Color = color;

	enemy->OnShoot = [this](ShooterEnemy& enemy)
	{
		OnEnemyShoot(enemy);
	};

	shooterEnemy.push_back(enemy);
	//_gameObjects.push_back(enemy);
}

void GameManager::CreateTurretEnemy(CustomVector2f position, float health, ColorType color) {
	TurretEnemy* enemy = poolManager->GetTurretEnemy(position, health, player);
	enemy->isAlive = true;
	enemy->pDie = [this](GameObject* go) { this->DestroyTurretEnemy(go); };
	(*enemy).Color = color;

	enemy->OnShoot = [this](TurretEnemy& enemy)
		{
			OnTurretEnemyShoot(enemy);
		};

	turretEnemy.push_back(enemy);
	//_gameObjects.push_back(enemy);
}

//fonction destruction
void GameManager::DestroyBullet(GameObject* item)
{
	Bullet* bullet = (Bullet*)item;
	poolManager->ReturnBullet(bullet);
	_bulletsToDestroy.push_back(bullet);
}

void GameManager::DestroyLightning(GameObject* item)
{
	LightningNode* lightning = (LightningNode*)item;
	_lightningToDestroy.push_back(lightning);
}

void GameManager::DestroyCollectible(GameObject* item) {
	Collectible* collectible = (Collectible*)item;
	_collectiblesToDestroy.push_back(collectible);
}

void GameManager::DestroyCacEnemy(GameObject* item)
{
	CACEnemy* cacEnemy = (CACEnemy*)item;
	poolManager->ReturnEnemy(cacEnemy);
	_cacEnemyToDestroy.push_back(cacEnemy);
	score += _scoreUpdate * _multiplicateur;
	if (RandomInt(0, 5) == 0) {
		CreateCollectible(cacEnemy->position);
	}
}

void GameManager::DestroyShooterEnemy(GameObject* item)
{
	ShooterEnemy* shooterEnemy = (ShooterEnemy*)item;
	poolManager->ReturnEnemy(shooterEnemy);
	_shooterEnemyToDestroy.push_back(shooterEnemy);
	score += _scoreUpdate * _multiplicateur;
	if (RandomInt(0, 5) == 0) {
		CreateCollectible(shooterEnemy->position);
	}
}

void GameManager::DestroyTurretEnemy(GameObject* item)
{
	TurretEnemy* turretEnemy = (TurretEnemy*)item;
	poolManager->ReturnEnemy(turretEnemy);
	_turretEnemyToDestroy.push_back(turretEnemy);
	score += _scoreUpdate * _multiplicateur;
	if (RandomInt(0, 5) == 0) {
		CreateCollectible(turretEnemy->position);
	}
}


void GameManager::SpawnEnemy(CustomVector2f windowSize) {
	ColorType color = ColorType::None;
	switch (RandomInt(0, 2)) {
		default:
		color = ColorType::Red;
			break;
		case 1 : 
			color = ColorType::Blue;
			break;
		case 2 : 
			color = ColorType::Green;
			break;
	}
	switch (RandomInt(0, 4))
	{
		case 0:
		case 1:
			CreateCacEnemy({ RandomFloat(0, windowSize.x),RandomFloat(0, windowSize.y) }, 100, color);
			break;
		case 2:
		case 3:
			CreateShooterEnemy({ RandomFloat(0, windowSize.x),RandomFloat(0, windowSize.y) }, 100, color);
			break;
		case 4:
			CreateTurretEnemy({ RandomFloat(0, windowSize.x),RandomFloat(0, windowSize.y) }, 100, color);
			break;
	}
	//CreateTurretEnemy({ RandomFloat(0, windowSize.x),RandomFloat(0, windowSize.y) }, 100, color);
}

//fonction shot
void GameManager::PlayerShoot()
{
	if (!player->CanShoot()) return;

	player->Shoot();
	CustomVector2f bulletSpawnLocalPos = Math::RotatePoint(player->bulletSpawnPos, CustomVector2f::zero, Math::ToRad(player->rotation));
	CustomVector2f pos = player->position + bulletSpawnLocalPos;

	CreateBullet(Team::Player, pos, player->speedBullet, player->GetLookDirection(), 10, player->GetColor());
}

void GameManager::OnEnemyShoot(ShooterEnemy& enemy)
{
	CustomVector2f bulletSpawnLocalPos = Math::RotatePoint(enemy.bulletSpawnPos, CustomVector2f::zero, Math::ToRad(enemy.rotation));
	CustomVector2f pos = enemy.position + bulletSpawnLocalPos;

	CreateBullet(Team::Enemy, pos, enemy.speedBullet, enemy.GetLookDirection(), enemy.damage, enemy.GetColor());
}

void GameManager::OnTurretEnemyShoot(TurretEnemy& enemy)
{
	CustomVector2f bulletSpawnLocalPos = Math::RotatePoint(enemy.bulletSpawnPos, CustomVector2f::zero, Math::ToRad(enemy.rotation));
	CustomVector2f pos = enemy.position + bulletSpawnLocalPos;

	CreateLightning(Team::Enemy, pos, enemy.GetLookDirection(), 1);
	enemy.lastLightningShooted = lightnings.back();
}

//fonction update
void GameManager::UpdateAll(float deltaTime)
{
	auto goIt = _gameObjects.begin();
	while (goIt != _gameObjects.end())
	{
		(*goIt)->Update(deltaTime);
		goIt++;
	}
}

void GameManager::UpdateDestroyItem()
{
	auto itGo = _gameObjects.begin();
	while (itGo != _gameObjects.end())
	{
		if (!(*itGo)->isAlive)
		{
			itGo = _gameObjects.erase(itGo);
		}
		else
		{
			itGo++;
		}
	}
}

//fonction get
int GameManager::GetPlayerHealth() const
{
	return player->health;
}

float GameManager::GetTime()
{
	return _time;
}

int GameManager::GetMultiplicateur() const
{
	return _multiplicateur;
}