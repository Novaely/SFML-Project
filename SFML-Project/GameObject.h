#pragma once

#include "Utils.h"
#include <iostream>
#include <cmath>

class GameObject
{
	public:
		GameObject();

		sf::Shape* shape = nullptr;

		ColorType color = ColorType::None;
		CustomVector2f position = CustomVector2f::zero;
		float rotation = 0.0f;

		virtual void Update(float deltaTime, sf::RenderWindow& window);

		ColorType GetColor();
		void SetColor(ColorType val);
		__declspec(property(get = GetColor, put = SetColor)) ColorType Color;
	
	protected :
		ColorType _color = ColorType::None;
		virtual void Active();
		virtual void Desactive();

	protected:
		bool _isActive = false;

		virtual void Draw(sf::RenderWindow& window);
};