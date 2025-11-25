#include "Player.h"

int Player::GetlevelShooter() {
	return _levelShooter;
}

void Player::SetlevelShooter(int val) {
	if (val > 0) {
		_levelShooter = val;
	}
}