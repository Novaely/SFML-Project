#pragma once

#include "Utils.h"
#include <iostream>
#include <cmath>
#include <map>

class GameObject
{

	public:
		GameObject();

		sf::Shape* shape = nullptr;
		CharaType characterType = CharaType::None;
		Team team = Team::None;

		CustomVector2f position = CustomVector2f::zero;
		float rotation = 0.0f;

		virtual void Update(float deltaTime, sf::RenderWindow& window);

		ColorType GetColor();
		void SetColor(ColorType val);
		__declspec(property(get = GetColor, put = SetColor)) ColorType Color;
		
		virtual void Active();
		virtual void Desactive();

		virtual void OnCollisionEnter(GameObject* other);

	protected:
		bool _isActive = false;
		ColorType _color = ColorType::None;
		std::map<ColorType, sf::Color> _colors = { {ColorType::None , sf::Color::Black}, {ColorType::Rouge , sf::Color::Red} , {ColorType::Bleu , sf::Color::Blue} , {ColorType::Vert , sf::Color::Green} };

		virtual void Draw(sf::RenderWindow& window);
};