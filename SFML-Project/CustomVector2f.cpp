#include "CustomVector2f.h"

// ----- Constructors
CustomVector2f::CustomVector2f() : x(0.0f), y(0.0f) {}
CustomVector2f::CustomVector2f(float _xy) : x(_xy), y(_xy) {}
CustomVector2f::CustomVector2f(float _x, float _y) : x(_x), y(_y) {}

// ----- Operators
//With CustomVector2f

CustomVector2f CustomVector2f::operator+(const CustomVector2f& other) const
{
	return CustomVector2f(x + other.x, y + other.y);
}

CustomVector2f CustomVector2f::operator-(const CustomVector2f& other) const
{
	return CustomVector2f(x - other.x, y - other.y);
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
	return x != other.x && y != other.y;
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