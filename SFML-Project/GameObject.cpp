#include "GameObject.h"

GameObject::GameObject() {}


void GameObject::Update(float deltaTime, sf::RenderWindow& window)
{
	shape->setPosition(position.x, position.y);
	shape->setRotation(rotation);

	Draw(window);
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if (!_isActive) return;
	if (shape != nullptr) window.draw(*shape);
}

void GameObject::Active()
{
	_isActive = true;
}

void GameObject::Desactive()
{
	_isActive = false;
}

ColorType GameObject::GetColor() {
	return _color;
}

void GameObject::SetColor(ColorType val) {
	_color = val;
}

void OnCollisionEnter(GameObject* other)
{
}