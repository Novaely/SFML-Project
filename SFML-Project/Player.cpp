#include "Player.h"

Player::Player() : Character() {
	Color = ColorType::Rouge;
	shape = new sf::CircleShape();
	shape->setFillColor(_colors[_color]);
	sf::CircleShape* pShape = (sf::CircleShape*)shape;
	pShape->setRadius(10);
	maxInputSpeed = 200;
	acceleration = 400;
	stopFriction = 400;
	turnBackFriction = 800;
	rotationSpeed = 0;
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