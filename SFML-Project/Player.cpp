#include "Player.h";

int Player::GetlevelShoter() {
	return _levelShoter;
}

int Player::SetlevelShoter(int val) {
	if (val > 0) {
		_levelShoter = val;
	}
}