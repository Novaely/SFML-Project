#include "Player.h"
#include "GameManager.h"

Player::Player() : Character() {
	Color = ColorType::Rouge;
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
	turnBackFriction = 800;
	rotationSpeed = 100;
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
	std::string text[] = {"none","red","blue","green"};
	switch (_color) {
		default : 
			_color = ColorType::Rouge;
			break;
		case ColorType::Rouge : 
			_color = ColorType::Bleu;
			break;
		case ColorType::Bleu : 
			_color = ColorType::Vert;
			break;
		case ColorType::Vert : 
			_color = ColorType::Rouge;
			break;
	}
	shape->setFillColor(_colors[_color]);
	//std::cout << "new color :" << text[(int)_color] << std::endl;
}

void Player::Shoot() {
	if (chronoShootAgain >= timerShootAgain)
	{
		chronoShootAgain = 0;
		(*gameManager).CreateBullet(Team::Player, position + bulletSpawnPos, speedBullet, Math::Polar2Cart(Math::ToRad(rotation), 1), 10);
	}
}