#include "Character.h"

Character::Character() : Movable() {


}

void Character::Update(float deltaTime, sf::RenderWindow& window) {
	Movable::Update(deltaTime, window);

	if (chronoShootAgain <= timerShootAgain) {
		chronoShootAgain += deltaTime;
	}
}