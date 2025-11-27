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

		float acceleration = 0;
		float stopFriction = 0;
		float turnBackFriction = 0;
		float rotationSpeed = 0;
		float rotationDirection = 0;

		void Update(float deltaTime, sf::RenderWindow& window) override;
		void Move(float deltaTime) override;
		void Rotate(float deltaTime);
};