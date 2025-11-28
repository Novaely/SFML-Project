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
	timerSpawnEnemies = 1;
	chronoSpawnEnemies = timerSpawnEnemies;
	QuelEnemy = false; // random plus tard
	spawnEnemy = false; //mettre en true si vous voulez avoir le spawn des ennemies
}
void GameManager::Update(float deltaTime)
{
	if (spawnEnemy) {
		if (chronoSpawnEnemies <= timerSpawnEnemies) {
			chronoSpawnEnemies += deltaTime;
		}
		else {
			chronoSpawnEnemies = 0;
			QuelEnemy = !QuelEnemy; // random plus tard
			if (QuelEnemy)
			{
				CreateCacEnemy({ 100,100 }, 100);
			}
			else
			{
				CreateShooterEnemy({ 200,200 }, 100);
			}
		}
	}
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

void GameManager::CreateCollectible() {
	//collectibles.push_back
}

void GameManager::CreateCacEnemy(CustomVector2f position, float health) {

	CACEnemy* enemy = (poolManager->GetCACEnemy(position, health, player));
	(*enemy).Color = ColorType::Bleu; // random plus tard
	(*enemy).shape->setFillColor(sf::Color::Blue); // random plus tard
	cacEnemy.push_back(enemy);
}

void GameManager::CreateShooterEnemy(CustomVector2f position, float health) {
	ShooterEnemy* enemy = poolManager->GetShooterEnemy(position, health, player);
	(*enemy).Color = ColorType::Vert; // random plus tard
	(*enemy).shape->setFillColor(sf::Color::Green);// random plus tard
	shooterEnemy.push_back(enemy);
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

	std::list<Collectible*>::iterator itemIt = collectibles.begin();
	while (itemIt != collectibles.end())
	{
		(*itemIt)->Update(deltaTime);
		itemIt++;
	}
}