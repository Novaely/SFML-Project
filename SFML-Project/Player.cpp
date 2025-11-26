#include "Player.h"

Player::Player() : Character() {
	Color = ColorType::Rouge;
	shape = new sf::ConvexShape();
	shape->setFillColor(_colors[_color]);
	sf::ConvexShape* pShape = (sf::ConvexShape*)shape;
	pShape->setPointCount(3);
	pShape->setPoint(0, sf::Vector2f{ 0,-10 });
	pShape->setPoint(1, sf::Vector2f{ 5, 5});
	pShape->setPoint(2, sf::Vector2f{ -5, 5});
	maxInputSpeed = 200;
	acceleration = 100;
	stopFriction = 20;
	turnBackFriction = 40;
	rotationSpeed = 100;
	Active();
}

int Player::GetlevelShooter() {
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
	std::cout << "new color :" << text[(int)_color] << std::endl;
}