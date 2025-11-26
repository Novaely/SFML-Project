#pragma once

#include "Utils.h"
#include <iostream>
#include <cmath>

class GameObject
{
	public:
		GameObject();

		ColorType color = ColorType::None;
		CustomVector2f position;
		float rotation;

		virtual void Update(float deltaTime, sf::RenderWindow& window);

		ColorType GetColor();
		void SetColor(ColorType val);
		__declspec(property(get = GetColor, put = SetColor)) ColorType Color;
	
	protected :
		ColorType _color = ColorType::None;
		virtual void Active();
		virtual void Desactive();
		virtual void Draw(sf::RenderWindow& window);
};