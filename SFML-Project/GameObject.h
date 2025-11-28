#pragma once

#include "Utils.h"
#include <map>

class GameObject
{
	public:
		GameObject();
		~GameObject();

		sf::Shape* shape = nullptr;

		CustomVector2f position = CustomVector2f::zero;
		float rotation = 0.0f;

		virtual void Update(float deltaTime);
		virtual void Draw(sf::RenderWindow& window);

		ColorType GetColor() const;
		void SetColor(ColorType val);
		__declspec(property(get = GetColor, put = SetColor)) ColorType Color;
		
		virtual void Active();
		virtual void Desactive();

		bool IsActive() const;

	protected:
		bool _isActive = false;
		ColorType _color = ColorType::None;
		std::map<ColorType, sf::Color> _colors = { {ColorType::None , sf::Color::Black}, {ColorType::Rouge , sf::Color::Red} , {ColorType::Bleu , sf::Color::Blue} , {ColorType::Vert , sf::Color::Green} };
};