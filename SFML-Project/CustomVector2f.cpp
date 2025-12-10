#include "CustomVector2f.h"
#include <iostream>
#include <cmath>

#pragma region Consts

const CustomVector2f CustomVector2f::zero = CustomVector2f(0);
const CustomVector2f CustomVector2f::one = CustomVector2f(1);
const CustomVector2f CustomVector2f::minusOne = CustomVector2f(-1);
const CustomVector2f CustomVector2f::right = CustomVector2f(1, 0);
const CustomVector2f CustomVector2f::down = CustomVector2f(0, -1);
const CustomVector2f CustomVector2f::left = CustomVector2f(-1, 0);
const CustomVector2f CustomVector2f::up = CustomVector2f(0, 1);

#pragma endregion


#pragma region Constructors

CustomVector2f::CustomVector2f() : x(0.0f), y(0.0f) {}
CustomVector2f::CustomVector2f(float _xy) : x(_xy), y(_xy) {}
CustomVector2f::CustomVector2f(float _x, float _y) : x(_x), y(_y) {}
CustomVector2f::CustomVector2f(const sf::Vector2f& v) : x(v.x), y(v.y) {}

#pragma endregion

#pragma region Operators

//With CustomVector2f

CustomVector2f CustomVector2f::operator+(const CustomVector2f& other) const
{
	return CustomVector2f(x + other.x, y + other.y);
}

CustomVector2f CustomVector2f::operator-(const CustomVector2f& other) const
{
	return CustomVector2f(x - other.x, y - other.y);
}

CustomVector2f CustomVector2f::operator-() const
{
	return CustomVector2f(-x, -y);
}

CustomVector2f CustomVector2f::operator*(const CustomVector2f& other) const
{
	return CustomVector2f(x * other.x, y * other.y);
}

CustomVector2f CustomVector2f::operator/(const CustomVector2f& other) const
{
	return CustomVector2f(x / other.x, y / other.y);
}

CustomVector2f& CustomVector2f::operator+=(const CustomVector2f& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

CustomVector2f& CustomVector2f::operator-=(const CustomVector2f& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

CustomVector2f& CustomVector2f::operator*=(const CustomVector2f& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

CustomVector2f& CustomVector2f::operator/=(const CustomVector2f& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

bool CustomVector2f::operator==(const CustomVector2f& other) const
{
	return x == other.x && y == other.y;
}

bool CustomVector2f::operator!=(const CustomVector2f& other) const
{
	return x != other.x || y != other.y;
}

CustomVector2f::operator sf::Vector2f() const
{ 
	return sf::Vector2f(x, y);
}

// With float

CustomVector2f CustomVector2f::operator+(const float& other) const
{
	return CustomVector2f(x + other, y + other);
}

CustomVector2f CustomVector2f::operator-(const float& other) const
{
	return CustomVector2f(x - other, y - other);
}

CustomVector2f CustomVector2f::operator*(const float& other) const
{
	return CustomVector2f(x * other, y * other);
}

CustomVector2f CustomVector2f::operator/(const float& other) const
{
	return CustomVector2f(x / other, y / other);
}

CustomVector2f& CustomVector2f::operator+=(const float& other)
{
	x += other;
	y += other;
	return *this;
}

CustomVector2f& CustomVector2f::operator-=(const float& other)
{
	x -= other;
	y -= other;
	return *this;
}

CustomVector2f& CustomVector2f::operator*=(const float& other)
{
	x *= other;
	y *= other;
	return *this;
}

CustomVector2f& CustomVector2f::operator/=(const float& other)
{
	x /= other;
	y /= other;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const CustomVector2f& v)
{
	os << "X: " << v.x << " Y: " << v.y;
	return os;
}

#pragma endregion

#pragma region Methods

float CustomVector2f::GetSquaredMagnitude() const
{
	return x * x + y * y;
}

float CustomVector2f::GetMagnitude() const 
{
	return std::sqrt(GetSquaredMagnitude());
}

CustomVector2f CustomVector2f::GetNormalised() const
{
	float length = GetMagnitude();
	if (length != 0) return CustomVector2f(x / length, y / length);
	return CustomVector2f();
}

void CustomVector2f::Normalise()
{
	float length = GetMagnitude();
	if (length != 0) *this /= length;
}

float CustomVector2f::GetAngle() const
{
	return std::atan2(y, x);
}

float CustomVector2f::AngleTo(const CustomVector2f& other) const
{
	CustomVector2f vecDirec = other - *this;
	return vecDirec.GetAngle();
}

float CustomVector2f::SquaredDistanceTo(const CustomVector2f& other) const
{
	CustomVector2f vecDirec = other - *this;
	return vecDirec.GetSquaredMagnitude();
}

float CustomVector2f::DistanceTo(const CustomVector2f& other) const
{
	CustomVector2f vecDirec = other - *this;
	return vecDirec.GetMagnitude();
}

CustomVector2f CustomVector2f::GetNormalCounterClockWise() const
{
	return CustomVector2f(-y, x);
}

CustomVector2f CustomVector2f::GetNormalClockWise() const
{
	return CustomVector2f(y, -x);
}

CustomVector2f CustomVector2f::DirectionTo(const CustomVector2f& other) const
{
	CustomVector2f vecDirec = other - *this;
	return vecDirec.GetNormalised();
}

float CustomVector2f::Dot(const CustomVector2f& other) const
{
	return x * other.x + y * other.y;
}

CustomVector2f CustomVector2f::Rotate(float angle) const
{
	float c = std::cos(angle);
	float s = std::sin(angle);
	return {
		x * c - y * s,
		x * s + y * c
	};
}

#pragma endregion

