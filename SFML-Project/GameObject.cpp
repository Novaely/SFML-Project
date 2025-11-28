#include "GameObject.h"

GameObject::GameObject() {}

void GameObject::Update(float deltaTime)
{
	shape->setPosition(position.x, position.y);
	shape->setRotation(rotation);
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if (shape != nullptr) window.draw(*shape);
}

void GameObject::Active()
{
	_isActive = true;
}

void GameObject::Desactive()
{
	_isActive = false;
	position = CustomVector2f::zero;
	SetColor(ColorType::None);
}

ColorType GameObject::GetColor() const {
	return _color;
}

void GameObject::SetColor(ColorType val) {
	_color = val;
	if (shape != nullptr)
	{
		shape->setFillColor(_colors[_color]);
	}
}

bool GameObject::IsActive() const
{
	return _isActive;
}

GameObject::~GameObject()
{
	if (shape != nullptr)
	{
		delete shape;
	}
}