#include "Player.h"

Player::Player() : Character() {
	characterType = CharaType::Player;
	Color = ColorType::Red;
	shape = new sf::ConvexShape();
	shape->setFillColor(_colors[_color]);
	sf::ConvexShape* pShape = (sf::ConvexShape*)shape;

	pShape->setOrigin(0, 0);
	pShape->setPointCount(3);
	pShape->setPoint(0, sf::Vector2f{ 15, 0});
	pShape->setPoint(1, sf::Vector2f{ -7.5f, 7.5f });
	pShape->setPoint(2, sf::Vector2f{ -7.5f, -7.5f });

	bulletSpawnPos = CustomVector2f(15, 0);

	maxInputSpeed = 200;
	acceleration = 400;
	stopFriction = 400;
	///turnBackFriction = 800;

	rotationSpeed = 200;
	timerShootAgain = 0.1f;
	speedBullet = 150;
	chronoShootAgain = timerShootAgain;
	Active();
}

int Player::GetlevelShooter() const {
	return _levelShooter;
}

void Player::SetlevelShooter(int val) {
	if (val > 0) {
		_levelShooter = val;
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
			std::cout << "Player hit by bullet Enemy" << std::endl;
			Damage(10);
		}
	}

	if (Other.characterType == CharaType::CACEnemy)
	{
		std::cout << "Player hit by CAC Enemy" << std::endl;
		Damage(10);
	}

	if (Other.characterType == CharaType::ShooterEnemy)
	{
		std::cout << "Player hit by Shooter Enemy" << std::endl;
		Damage(10);
	}

	if (Other.characterType == CharaType::Lighting)
	{
		std::cout << "Player hit by Lightning";
	}
}

void Player::Damage(float dmg)
{
	health -= dmg;
	if (health <= 0)
	{
		isAlive = false;
		std::cout << "fin du jeu" << std::endl;
		//cut le jeu
	}
}