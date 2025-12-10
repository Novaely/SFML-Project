#include "GameObject.h"

std::map<int, std::function<void(GameObject*)>> GameObject::_createListeners;

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
	NotifyCreated(this);
}

int GameObject::AddCreateListener(const std::function<void(GameObject*)>& func)
{
	int id = _createListeners.size();
	_createListeners[id] = func;
	return id;
}

void GameObject::RemoveCreateListener(const int id)
{
	_createListeners.erase(id);
}

void GameObject::NotifyCreated(GameObject* go)
{
	for (auto& listener : _createListeners)
	{
		listener.second(go);
	}
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

void GameObject::OnCollisionEnter(GameObject* other)
{
}

void GameObject::Destroy()
{
	_isActive = false;
	isAlive = false;
	if (pDie != nullptr)
	{
		pDie(this);
	}
}