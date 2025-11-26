#pragma once
#include "Movable.h"

class Character : public Movable
{
	public : 
		Character();
		float health = 0;
		float speedBullet = 0;
		float timerShootAgain = 0;
		float chronoShootAgain = 0;

		void Update(float deltaTime, sf::RenderWindow& window) override;
};