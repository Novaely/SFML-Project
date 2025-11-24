#pragma once

#include "CustomVector2f.h";

class GameObject
{
	public:
		CustomVector2f position;
		float rotation;

		virtual void Update(float deltaTime);

	protected :
		virtual void Draw();
};