#pragma once

#include "Utils.h"
#include <iostream>
#include <cmath>

class GameObject
{
	public:
		
		CustomVector2f position;
		float rotation;

		virtual void Update(float deltaTime);

		ColorType GetColor();
		void SetColor(ColorType val);
		__declspec(property(get = GetColor, put = SetColor)) ColorType Color;
	
	protected :
		ColorType _color = ColorType::None;
		virtual void Draw();
};