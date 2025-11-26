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
	if (shape != nullptr) window.draw(*shape);
}
void GameObject::Active() {}
void GameObject::Desactive() {}