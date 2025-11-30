#pragma once

#include "Utils.h"
#include <map>
#include <functional>

class GameObject
{

	public:
		GameObject();
		~GameObject();

		sf::Shape* shape = nullptr;
		CharaType characterType = CharaType::None;
		Team team = Team::None;

		CustomVector2f position = CustomVector2f::zero;
		float rotation = 0.0f;
		bool isAlive = true;

		virtual void Update(float deltaTime);
		virtual void Draw(sf::RenderWindow& window);

		ColorType GetColor() const;
		void SetColor(ColorType val);
		__declspec(property(get = GetColor, put = SetColor)) ColorType Color;
		
		virtual void Active();
		virtual void Desactive();

		bool IsActive() const;

		virtual void OnCollisionEnter(GameObject* other);
		std::function<void(GameObject*)> pDie;

	protected:
		bool _isActive = false;
		ColorType _color = ColorType::None;
		std::map<ColorType, sf::Color> _colors = { {ColorType::None , sf::Color::Black}, {ColorType::Rouge , sf::Color::Red} , {ColorType::Bleu , sf::Color::Blue} , {ColorType::Vert , sf::Color::Green} };
};