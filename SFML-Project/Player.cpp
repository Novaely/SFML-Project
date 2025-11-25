#include "Player.h";

int Player::GetlevelShoter() {
	return _levelShoter;
}

void Player::SetlevelShoter(int val) {
	if (val > 0) {
		_levelShoter = val;
	}
}