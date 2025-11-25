#pragma once

#include "Utils.h"
#include <iostream>
#include <cmath>

class GameObject
{
	public:
		ColorType color = ColorType::None;
		CustomVector2f position;
		float rotation;

		virtual void Update(float deltaTime);

	protected :
		virtual void Draw();
};