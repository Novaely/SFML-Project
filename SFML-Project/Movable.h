#pragma once

#include "GameObject.h"

class Movable : public GameObject
{
	public:
		Movable();

		float speed = 0;

		float maxInputSpeed = 0;

		float damage = 0;

		CustomVector2f inputDirection = CustomVector2f::zero;
		CustomVector2f moveDirection = CustomVector2f::zero;

		void Update(float deltaTime) override;


	protected:
		virtual void Move(float deltaTime);
};