#pragma once

#include "Utils.h"
#include <iostream>
#include <cmath>

class GameObject
{
	private:
		ColorType _color = ColorType::None;
	public:
		
		CustomVector2f position;
		float rotation;

		virtual void Update(float deltaTime);

		ColorType GetColor();
		void SetColor(ColorType cal);
		__declspec(property(get = GetColor, put = SetColor)) int Color;
	
	protected :
		virtual void Draw();
};