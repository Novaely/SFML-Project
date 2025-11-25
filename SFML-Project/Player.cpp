#include "Player.h"

Player::Player() {
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
	std::cout << "switch color" << std::endl;
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
	std::cout << "new color :" << text[(int)_color] << std::endl;
}