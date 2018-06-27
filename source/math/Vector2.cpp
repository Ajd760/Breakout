#include "Vector2.h"
//TODO: THIS IS INCOMPLETE
Vector2::Vector2()
{
	x = y = 0.0f;
}

Vector2::Vector2(const float& x, const float& y)
{
	this->x = x; this->y = y;
}

Vector2& Vector2::add(const Vector2& other)
{
	this->x += other.x; this->y += other.y;
	return (*this);
}
Vector2& Vector2::subtract(const Vector2& other)
{
	this->x -= other.x; this->y -= other.y;
	return (*this);
}
Vector2& Vector2::multiply(const Vector2& other)
{
	this->x *= other.x; this->y *= other.y;
	return (*this);
}
Vector2& Vector2::divide(const Vector2& other)
{
	this->x /= other.x; this->y /= other.y;
	return (*this);
}

Vector2 operator+(Vector2 left, const Vector2& right)
{
	return left.add(right);
}
Vector2 operator-(Vector2 left, const Vector2& right)
{
	return left.subtract(right);
}
Vector2 operator*(Vector2 left, const Vector2& right)
{
	return left.multiply(right);
}
Vector2 operator/(Vector2 left, const Vector2& right)
{
	return left.divide(right);
}

float Vector2::Dot(const Vector2& left, const Vector2& right)
{
	return (left.x*right.x + right.x*right.y);
}




