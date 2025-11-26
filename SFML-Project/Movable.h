#pragma once

#include "GameObject.h"

class Movable : public GameObject
{
	public:
		Movable();

		float speed;
		float maxInputSpeed;

		float acceleration;
		float stopFriction;
		float turnBackFriction;

		CustomVector2f inputDirection;
		CustomVector2f moveDirection;

		void Update(float deltaTime, sf::RenderWindow& window) override;

	protected:
		void Move(float deltaTime);
};