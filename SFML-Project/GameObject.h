#pragma once

#include "CustomVector2f.h";
#include "Utils.h";

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