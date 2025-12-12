#pragma once

#include "Utils.h"
#include <map>
#include <functional>
#include <list>

class GameObject
{
	public:
		// ===== VARIABLES ===== //

		// Collisions //
		LayerMask layer = CollisionLayer::Layer_None;
		LayerMask collisionMask = CollisionLayer::Layer_All;
		ShapeType shapeType = ShapeType::None;
		float broadRadius = 0;

		// Game //
		bool isAlive = true;
		Team team = Team::None;
		float damage = 0;

		// transform //
		CustomVector2f position = CustomVector2f::zero;
		float rotation = 0.0f;

		// Other //
		sf::Shape* shape = nullptr;

		// ===== FUNCTIONS ===== //

		// Constructor //
		GameObject();

		// Destructor //
		~GameObject();

		// Getters / Setters //
		bool IsActive() const;
		ColorType GetColor() const;
		void SetColor(ColorType val);
		__declspec(property(get = GetColor, put = SetColor)) ColorType Color;

		// Collisions //
		virtual void OnCollisionEnter(GameObject* other);

		// Game //
		virtual void Update(float deltaTime);
		virtual void Draw(sf::RenderWindow& window);
		virtual void Active();
		virtual void Desactive();
		virtual void Destroy();

		static int AddCreateListener(const std::function<void(GameObject*)>& func);
		static void RemoveCreateListener(const int id);
		static void NotifyCreated(GameObject* go);

		// Others //
		std::function<void(GameObject*)> pDie;

	protected:
		// ===== VARIABLES ===== //

		// Game //
		bool _isActive = false;
		ColorType _color = ColorType::None;

		std::map<ColorType, sf::Color> _colors =
		{
			{ColorType::None , sf::Color::Transparent},
			{ColorType::Red , sf::Color::Red},
			{ColorType::Blue , sf::Color::Cyan},
			{ColorType::Green , sf::Color(0, 166, 0)},
			{ColorType::Orange , sf::Color(255,132,0)},
			{ColorType::Pink, sf::Color(255,0,236)},
			{ColorType::Yellow, sf::Color::Yellow }

		};

		static std::map<int, std::function<void(GameObject*)>> _createListeners;

		// ===== FUNCTIONS ===== //

		// Collisions //
		void SetBroadRadiusFromPoints(const Vec2f points[], int numPoints);
};