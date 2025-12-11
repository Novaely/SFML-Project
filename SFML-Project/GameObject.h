#pragma once

#include "Utils.h"
#include <map>
#include <functional>
#include <list>

class GameObject
{

	public:
		GameObject();
		~GameObject();

		sf::Shape* shape = nullptr;
		ShapeType shapeType = ShapeType::None;
		CharaType characterType = CharaType::None;
		CollisionLayer layer = CollisionLayer::None;
		LayerMask collisionMask = static_cast<LayerMask>(CollisionLayer::All);
		float broadRadius = 0;
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

		static int AddCreateListener(const std::function<void(GameObject*)>& func);
		static void RemoveCreateListener(const int id);
		static void NotifyCreated(GameObject* go);

		virtual void Destroy();

	protected:
		bool _isActive = false;
		ColorType _color = ColorType::None;
		std::map<ColorType, sf::Color> _colors = { {ColorType::None , sf::Color::Transparent}, {ColorType::Red , sf::Color::Red} , {ColorType::Blue , sf::Color::Cyan} , {ColorType::Green , sf::Color(0, 166, 0)} , {ColorType::Yellow , sf::Color::Yellow}};
		
		static std::map<int, std::function<void(GameObject*)>> _createListeners;
		void SetBroadRadiusFromPoints(const Vec2f points[], int numPoints);
};