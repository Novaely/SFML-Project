#pragma once

#include "GameObject.h"

class Movable : public GameObject
{
	public:
		Movable();

		float speed = 0;
		float maxInputSpeed = 0;

		float acceleration = 0;
		float stopFriction = 0;
		float turnBackFriction = 0;
		float rotationSpeed = 0;

		float damage = 0;

		CustomVector2f inputDirection = CustomVector2f::right;
		CustomVector2f moveDirection = CustomVector2f::zero;

		void Update(float deltaTime, sf::RenderWindow& window) override;

	protected:
		void Move(float deltaTime);
};