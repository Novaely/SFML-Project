#include "Player.h"

Player::Player() : Character() {
	shapeType = ShapeType::Convex;

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

	layer = CollisionLayer::Layer_Player;
	collisionMask = static_cast<LayerMask>(CollisionLayer::Layer_BulletEnemy) |
		static_cast<LayerMask>(CollisionLayer::Layer_Enemy) | static_cast<LayerMask>(CollisionLayer::Layer_Collectible);

	bulletSpawnPos = CustomVector2f(15, 0);
	speedBullet = 150;
	timerShootAgain = 0.1f;
	chronoShootAgain = timerShootAgain;

	maxInputSpeed = 200;
	acceleration = 1600;
	stopFriction = 800;
	turnBackFriction = 1600;
	rotationSpeed = 200;

	health = 5;
	maxHealth = 5;

	Active();
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

int Player::GetlevelShooter() const {
	return _levelShooter;
}

void Player::SetlevelShooter(int val) {
	if (val > 0) {
		_levelShooter = val;
		Math::Clamp((float)_levelShooter, 0, (float)_levelShooterMax);
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
	const GameObject& pOther = *(other);

	if (pOther.layer == Layer_Enemy || pOther.layer == Layer_BulletEnemy)
	{
		Damage(((GameObject*)other)->damage);
	}
}

float Player::GetMaxHealth() const {
	return maxHealth;
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
		}
	}
}