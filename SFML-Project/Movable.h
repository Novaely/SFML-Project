#pragma once

#include "GameObject.h"

class Movable : public GameObject
{
	public:
		// Constructor
		Movable();

		//Variables
		float speed = 0;
		float maxInputSpeed = 0;

		CustomVector2f inputDirection = CustomVector2f::zero;
		CustomVector2f moveDirection = CustomVector2f::zero;

		//Functions
		void Update(float deltaTime) override;


	protected:
		//Functions
		virtual void Move(float deltaTime);
};