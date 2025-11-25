#include "GameObject.h"

void GameObject::Update(float deltaTime) {}

ColorType GameObject::GetColor() {
	return _color;
}

void GameObject::SetColor(ColorType val) {
	_color = val;
}