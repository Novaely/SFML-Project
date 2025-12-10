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
	_numberOfEnemyForWave = 5;
	_numberOfEnemyUp = 1;
	_numberOfWaveBeforeUpNumberOfEnemy = 5;
	_timerSpawnEnemies = 10;
	_wave = 0;
	_chronoSpawnEnemies = _timerSpawnEnemies;
	_wantSpawnEnemy = true; //mettre en true si vous voulez avoir le spawn des ennemies
	_idGameObjectCreateListener = GameObject::AddCreateListener([this](GameObject* go)
		{
			NewGameObjectCreated(go);
		});
	_radiusSpawnEnemy = (150, 150);
}

void GameManager::NewGameObjectCreated(GameObject* go)
{
	gameObjects.push_back(go);
}

void GameManager::Update(float deltaTime, CustomVector2f windowSize)
{
	_time += deltaTime;

	if (_wantSpawnEnemy) {
		if (_enemies.size() == 0 || _chronoSpawnEnemies >= _timerSpawnEnemies) {
			_chronoSpawnEnemies = 0;
			SpawnWaveEnemy(windowSize);
			_wave++;
			if (_wave % _numberOfWaveBeforeUpNumberOfEnemy) {
				_numberOfEnemyForWave += _numberOfEnemyUp;
			}
		}
		else {
			_chronoSpawnEnemies += deltaTime;
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
	auto goIt = gameObjects.begin();
	while (goIt != gameObjects.end()) 
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
	if((*player).LevelShooter >= 3)
	{
		return;
	}
	(*player).LevelShooter += 1;
}

//fonction Creatation
void GameManager::CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType)
{
	Bullet* bullet = poolManager->GetBullet(team, position, speed, direction, damage, colorType);
	bullet->isAlive = true;
}

LightningNode* GameManager::CreateLightning(Team team, CustomVector2f position, CustomVector2f direction, float damage)
{
	LightningNode* lightning = new LightningNode();
	lightning->isAlive = true;
	lightning->damages = damage;
	lightning->team = team;
	lightning->startPoint = position;
	lightning->endPoint = position + direction * 1000;

	lightning->StartLightning();
	lightning->Active();

	return lightning;
}

void GameManager::CreateCollectible(CustomVector2f position) {
	Collectible* collectible = new Collectible();
	collectible->Color = ColorType::Yellow;
	collectible->position = position;
	collectible->isAlive = true;
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
}

void GameManager::CreateCacEnemy(CustomVector2f position, float health,ColorType color) {

	CACEnemy* enemy = (poolManager->GetCACEnemy(position, health, player));
	enemy->isAlive = true;
	enemy->pDie = [this](GameObject* go) { this->DestroyCacEnemy(go); };
	(*enemy).Color = color;
	_enemies.push_back(enemy);
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
	_enemies.push_back(enemy);
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
	_enemies.push_back(enemy);
}

//fonction destruction
void GameManager::DestroyCacEnemy(GameObject* item)
{
	CACEnemy* cacEnemy = (CACEnemy*)item;
	poolManager->ReturnEnemy(cacEnemy);
	score += _scoreUpdate * _multiplicateur;
	if (RandomInt(0, 5) == 0) {
		CreateCollectible(cacEnemy->position);
	}
	_enemies.remove(cacEnemy);
}

void GameManager::DestroyShooterEnemy(GameObject* item)
{
	ShooterEnemy* shooterEnemy = (ShooterEnemy*)item;
	poolManager->ReturnEnemy(shooterEnemy);
	score += _scoreUpdate * _multiplicateur;
	if (RandomInt(0, 5) == 0) {
		CreateCollectible(shooterEnemy->position);
	}
	_enemies.remove(shooterEnemy);
}

void GameManager::DestroyTurretEnemy(GameObject* item)
{
	TurretEnemy* turretEnemy = (TurretEnemy*)item;
	poolManager->ReturnEnemy(turretEnemy);
	score += _scoreUpdate * _multiplicateur;
	if (RandomInt(0, 5) == 0) {
		CreateCollectible(turretEnemy->position);
	}
	_enemies.remove(turretEnemy);
}

void GameManager::SpawnWaveEnemy(CustomVector2f windowSize) {
	for (int i = 0; i < _numberOfEnemyForWave;i++) {
		SpawnEnemy(windowSize);
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
			CreateCacEnemy({ Math::Clamp(RandomFloat(0, windowSize.x),player->position.x - _radiusSpawnEnemy.x,windowSize.x),Math::Clamp(RandomFloat(0, windowSize.y),player->position.y - _radiusSpawnEnemy.y,windowSize.y) }, 100, color);
			break;
		case 2:
		case 3:
			CreateShooterEnemy({ RandomFloat(0, windowSize.x),RandomFloat(0, windowSize.y) }, 100, color);
			break;
		case 4:
			CreateTurretEnemy({ RandomFloat(0, windowSize.x),RandomFloat(0, windowSize.y) }, 100, color);
			break;
	}
}

//fonction shot
void GameManager::PlayerShoot()
{
	if (!player->CanShoot()) return;

	player->Shoot();
	CustomVector2f bulletSpawnLocalPos = Math::RotatePoint(player->bulletSpawnPos, CustomVector2f::zero, Math::ToRad(player->rotation));
	CustomVector2f pos = player->position + bulletSpawnLocalPos;
	switch (player->LevelShooter)
	{
	case 1:
		CreateBullet(Team::Player, pos, player->speedBullet, player->GetLookDirection(), 10, player->GetColor());
		break;
	case 2:
		CreateBullet(Team::Player, pos, player->speedBullet, player->GetLookDirection().Rotate(Math::ToRad(15)), 10, player->GetColor());
		CreateBullet(Team::Player, pos, player->speedBullet, player->GetLookDirection().Rotate(Math::ToRad(-15)), 10, player->GetColor());
		break;
	case 3:
		CreateBullet(Team::Player, pos, player->speedBullet, player->GetLookDirection().Rotate(Math::ToRad(15)), 10, player->GetColor());
		CreateBullet(Team::Player, pos, player->speedBullet, player->GetLookDirection(), 10, player->GetColor());
		CreateBullet(Team::Player, pos, player->speedBullet, player->GetLookDirection().Rotate(Math::ToRad(-15)), 10, player->GetColor());
		break;
	default:
		break;
	}
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

	enemy.lastLightningShooted = CreateLightning(Team::Enemy, pos, enemy.GetLookDirection(), 1);
}

//fonction update
void GameManager::UpdateAll(float deltaTime)
{
	auto goIt = gameObjects.begin();
	while (goIt != gameObjects.end())
	{
		(*goIt)->Update(deltaTime);
		goIt++;
	}
}

void GameManager::UpdateDestroyItem()
{
	auto itGo = gameObjects.begin();
	while (itGo != gameObjects.end())
	{
		if (!(*itGo)->isAlive)
		{
			itGo = gameObjects.erase(itGo);
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
int GameManager::GetLevel() const
{
	return player->LevelShooter;
}
int GameManager::GetFPS() const
{
	return fps;
}