#include "GameObject.h"

GameObject::GameObject() : position(CustomVector2f(0)), rotation(0), color(ColorType::None) {}

void GameObject::Update(float deltaTime, sf::RenderWindow& window)
{
	Draw(window);
}

void GameObject::Draw(sf::RenderWindow& window) {}

ColorType GameObject::GetColor() {
	return _color;
}

void GameObject::SetColor(ColorType val) {
	_color = val;
}
void GameObject::Active() {}
void GameObject::Desactive() {}