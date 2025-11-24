#pragma once

#include "GameObject.h"

class Movable : public GameObject
{
	public:
		float speed;
		float maxSpeed;

		float axxeleration;
		float stopFriction;
		float turnBackFriction;

		CustomVector2f inputDirection;
		CustomVector2f moveDirection;

	protected:
		void Move();
};