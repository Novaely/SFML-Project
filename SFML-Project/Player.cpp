#include "Player.h"

Player::Player() : Character() {
	characterType = CharaType::Player;
	shapeType = ShapeType::Convex;

	layer = CollisionLayer::Player;
	collisionMask = static_cast<LayerMask>(CollisionLayer::BulletEnemy) |
		static_cast<LayerMask>(CollisionLayer::Enemy) | static_cast<LayerMask>(CollisionLayer::Collectible);

	Color = ColorType::Red;
	shape = new sf::ConvexShape();
	shape->setFillColor(_colors[_color]);
	sf::ConvexShape* pShape = (sf::ConvexShape*)shape;

	pShape->setOrigin(0, 0);
	pShape->setPointCount(3);
	pShape->setPoint(0, sf::Vector2f{ 15, 0});
	pShape->setPoint(1, sf::Vector2f{ -7.5f, 7.5f });
	pShape->setPoint(2, sf::Vector2f{ -7.5f, -7.5f });

	Vec2f points[3] = { pShape->getPoint(0), pShape->getPoint(1) , pShape->getPoint(2) };
	SetBroadRadiusFromPoints(points, 3);

	bulletSpawnPos = CustomVector2f(15, 0);

	maxInputSpeed = 200;
	acceleration = 400;
	stopFriction = 400;

	rotationSpeed = 200;
	timerShootAgain = 0.1f;
	speedBullet = 150;
	chronoShootAgain = timerShootAgain;
	health = 5;
	maxHealth = 5;
	Active();
}

int Player::GetlevelShooter() const {
	return _levelShooter;
}

void Player::SetlevelShooter(int val) {
	if (val > 0) {
		_levelShooter = val;
		Math::Clamp(_levelShooter, 0, _levelShooterMax);
	}
}

void Player::SwitchColor()
{
	switch (_color) {
		default : 
			Color = ColorType::Red;
			break;
		case ColorType::Red : 
			Color = ColorType::Blue;
			break;
		case ColorType::Blue : 
			Color = ColorType::Green;
			break;
		case ColorType::Green : 
			Color = ColorType::Red;
			break;
	}
}

void Player::Shoot() {
	if (chronoShootAgain >= timerShootAgain)
	{
		chronoShootAgain = 0;
		_canShoot = false;
	}
}

void Player::OnCollisionEnter(GameObject* other)
{
	const GameObject& Other = *(other);
	if (Other.characterType == CharaType::Bullet)
	{
		if (Other.team == Team::Enemy)
		{
			//std::cout << "Player hit by bullet Enemy" << std::endl;
			Damage(((Movable*)other)->damage);
		}
	}

	if (Other.characterType == CharaType::CACEnemy)
	{
		//std::cout << "Player hit by CAC Enemy" << std::endl;
		Damage(((Movable*)other)->damage);
	}

	if (Other.characterType == CharaType::ShooterEnemy)
	{
		//std::cout << "Player hit by Shooter Enemy" << std::endl;
		Damage(((Movable*)other)->damage);
	}

	if (Other.characterType == CharaType::Lighting)
	{
		//std::cout << "Player hit by Lightning" << std::endl;
		Damage(((LightningNode*)other)->damages);
	}
}

void Player::Damage(float dmg)
{
	if (!_isInvicible)
	{
		if(_levelShooter != 1)
		{
			_levelShooter -= 1;
		}
		health -= dmg;
		_isInvicible = true;
		_timeSinceInvincible = 0.0f;
		if (health <= 0)
		{
			isAlive = false;
			//std::cout << "fin du jeu" << std::endl;
			//cut le jeu
		}
	}
}

void Player::Update(float deltaTime)
{
	Character::Update(deltaTime);
	if (_isInvicible)
	{
		_timeSinceInvincible += deltaTime;
		_timeSinceColorChange += deltaTime;
		if (_timeSinceColorChange >= 0.1f)
		{
			_timeSinceColorChange = 0.0f;
			if (shape->getFillColor() == sf::Color::White)
			{
				shape->setFillColor(_colors[_color]);
			}
			else
			{
				shape->setFillColor(sf::Color::White);
			}
		}
			
		if(_timeSinceInvincible >= _invicibleTime)
		{
			_isInvicible = false;
			_timeSinceInvincible = 0.0f;
			shape->setFillColor(_colors[_color]);
		}
	}
}

float Player::GetMaxHealth() const {
	return maxHealth;
}