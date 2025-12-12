#include "GameObject.h"

// ===== VARIABLES ===== //
std::map<int, std::function<void(GameObject*)>> GameObject::_createListeners;

// ===== FUNCTIONS ===== //

// ===== PUBLIC ===== //

// Constructor //
GameObject::GameObject() {}

// Destructor //
GameObject::~GameObject()
{
	if (shape != nullptr)
	{
		delete shape;
	}
}

// Getters / Setters //
bool GameObject::IsActive() const
{
	return _isActive;
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

// Collisions //
void GameObject::OnCollisionEnter(GameObject* other) {}

// Game //
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

void GameObject::Desactive()
{
	_isActive = false;
	position = CustomVector2f::zero;
	SetColor(ColorType::None);
}

void GameObject::Destroy()
{
	if (!isAlive) return;

	_isActive = false;
	isAlive = false;
	if (pDie != nullptr)
	{
		pDie(this);
	}
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

// ===== PROTECTED ===== //

// Collisions //
void GameObject::SetBroadRadiusFromPoints(const Vec2f points[], int numPoints)
{
	float maxDist = 0;
	float currentDist = 0;
	Vec2f point = Vec2f::zero;
	for (int i = 0; i < numPoints; i++)
	{
		currentDist = points[i].GetSquaredMagnitude();
		if (currentDist > maxDist)
		{
			maxDist = currentDist;
			point = points[i];
		}
	}
	broadRadius = point.GetMagnitude();
}