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
	_numberOfEnemyUp = 2;
	_numberOfWaveBeforeUpNumberOfEnemy = 3;
	_timerSpawnEnemies = 10;
	_chronoSpawnEnemies = _timerSpawnEnemies;
	_wantSpawnEnemy = true; //mettre en true si vous voulez avoir le spawn des ennemies
}

void GameManager::Update(float deltaTime, CustomVector2f windowSize)
{
	_time += deltaTime;

	if (_wantSpawnEnemy) {
		if (_enemies.size() == 0 || _chronoSpawnEnemies >= _timerSpawnEnemies) {
			_chronoSpawnEnemies = 0;
			SpawnWaveEnemy(windowSize);
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
	if(player->health == 0)
	{
		pause = true;
	}
}

void GameManager::Draw(sf::RenderWindow& window)
{
	player->Draw(window);

	auto lightningIt = lightnings.begin();
	while (lightningIt != lightnings.end())
	{
		(*lightningIt)->Draw(window);
		lightningIt++;
	}

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

	std::list<TurretEnemy*>::iterator turretIt = turretEnemy.begin();
	while (turretIt != turretEnemy.end())
	{
		(*turretIt)->Draw(window);
		turretIt++;
	}

	auto collectibleIt = collectibles.begin();
	while (collectibleIt != collectibles.end())
	{
		(*collectibleIt)->Draw(window);
		collectibleIt++;
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
	bullet->pDie = [this](GameObject* go) { this->DestroyBullet(go); };
	bullets.push_back(bullet);
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
}

void GameManager::CreateCacEnemy(CustomVector2f position, float health,ColorType color) {

	CACEnemy* enemy = (poolManager->GetCACEnemy(position, health, player));
	enemy->isAlive = true;
	enemy->pDie = [this](GameObject* go) { this->DestroyCacEnemy(go); };
	(*enemy).Color = color;
	cacEnemy.push_back(enemy);
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

	shooterEnemy.push_back(enemy);
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

	turretEnemy.push_back(enemy);
	_enemies.push_back(enemy);
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
	_enemies.remove(cacEnemy);
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
	_enemies.remove(shooterEnemy);
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
	/*switch (RandomInt(0, 4))
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
	}*/
	CreateTurretEnemy({ RandomFloat(0, windowSize.x),RandomFloat(0, windowSize.y) }, 100, color);
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

	CreateLightning(Team::Enemy, pos, enemy.GetLookDirection(), 1);
	enemy.lastLightningShooted = lightnings.back();
}

//fonction update
void GameManager::UpdateAll(float deltaTime) {
	player->Update(deltaTime);

	auto lightningIt = lightnings.begin();
	while (lightningIt != lightnings.end())
	{
		(*lightningIt)->Update(deltaTime);
		lightningIt++;
	}

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

	std::list<TurretEnemy*>::iterator turretIt = turretEnemy.begin();
	while (turretIt != turretEnemy.end())
	{
		(*turretIt)->Update(deltaTime);
		turretIt++;
	}

	std::list<Collectible*>::iterator itemIt = collectibles.begin();
	while (itemIt != collectibles.end())
	{
		(*itemIt)->Update(deltaTime);
		itemIt++;
	}
}

void GameManager::UpdateDestroyItem() {
	//check destroy Bullets
	auto itToDestroyBullets = _bulletsToDestroy.begin();
	while (itToDestroyBullets != _bulletsToDestroy.end()) {
		auto itBullets = bullets.begin();
		while (itBullets != bullets.end()) {
			if ((*itBullets) == (*itToDestroyBullets)) {
				itBullets = bullets.erase(itBullets);
			}
			else {
				itBullets++;
			}
		}
		itToDestroyBullets = _bulletsToDestroy.erase(itToDestroyBullets);
	}

	//check destroy CacEnemy
	auto itToDestroyCacEnemy = _cacEnemyToDestroy.begin();
	while (itToDestroyCacEnemy != _cacEnemyToDestroy.end()) {
		auto itCacEnemy = cacEnemy.begin();
		while (itCacEnemy != cacEnemy.end()) {
			if ((*itCacEnemy) == (*itToDestroyCacEnemy)) {
				itCacEnemy = cacEnemy.erase(itCacEnemy);
			}
			else {
				itCacEnemy++;
			}
		}
		itToDestroyCacEnemy = _cacEnemyToDestroy.erase(itToDestroyCacEnemy);
	}

	//check destroy ShooterEnemy
	auto itToDestroyShooterEnemy = _shooterEnemyToDestroy.begin();
	while (itToDestroyShooterEnemy != _shooterEnemyToDestroy.end()) {
		auto itShooterEnemy = shooterEnemy.begin();
		while (itShooterEnemy != shooterEnemy.end()) {
			if ((*itShooterEnemy) == (*itToDestroyShooterEnemy)) {
				itShooterEnemy = shooterEnemy.erase(itShooterEnemy);
			}
			else {
				itShooterEnemy++;
			}
		}
		itToDestroyShooterEnemy = _shooterEnemyToDestroy.erase(itToDestroyShooterEnemy);
	}

	//check destroy TurretEnemy
	auto itToDestroyTurretEnemy = _turretEnemyToDestroy.begin();
	while (itToDestroyTurretEnemy != _turretEnemyToDestroy.end()) {
		auto itTurretEnemy = turretEnemy.begin();
		while (itTurretEnemy != turretEnemy.end()) {
			if ((*itTurretEnemy) == (*itToDestroyTurretEnemy)) {
				itTurretEnemy = turretEnemy.erase(itTurretEnemy);
			}
			else {
				itTurretEnemy++;
			}
		}
		itToDestroyTurretEnemy = _turretEnemyToDestroy.erase(itToDestroyTurretEnemy);
	}

	//check destroy lightning
	auto itToDestroyLightning = _lightningToDestroy.begin();
	while (itToDestroyLightning != _lightningToDestroy.end())
	{
		auto itLightning = lightnings.begin();
		while (itLightning != lightnings.end())
		{
			if ((*itLightning) == (*itToDestroyLightning))
			{
				delete *itLightning;
				itLightning = lightnings.erase(itLightning);
			}
			else
			{
				itLightning++;
			}
		}
		itToDestroyLightning = _lightningToDestroy.erase(itToDestroyLightning);
	}

	//check destroy collectible
	auto itToDestroyCollectible = _collectiblesToDestroy.begin();
	while (itToDestroyCollectible != _collectiblesToDestroy.end())
	{
		auto itCollectible = collectibles.begin();
		while (itCollectible != collectibles.end())
		{
			if ((*itCollectible) == (*itToDestroyCollectible))
			{
				delete* itCollectible;
				itCollectible = collectibles.erase(itCollectible);
			}
			else
			{
				itCollectible++;
			}
		}
		itToDestroyCollectible = _collectiblesToDestroy.erase(itToDestroyCollectible);
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