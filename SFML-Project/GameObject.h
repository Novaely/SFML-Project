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

		virtual void Active();
		virtual void Desactive();
	protected:
		virtual void Draw(sf::RenderWindow& window);
};