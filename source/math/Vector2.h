#pragma once


struct Vector2
{
	float x, y;

	Vector2();
	Vector2(const float& x, const float& y);
	
	Vector2& add(const Vector2& other);
	Vector2& subtract(const Vector2& other);
	Vector2& multiply(const Vector2& other);
	Vector2& divide(const Vector2& other);

	friend Vector2 operator+(Vector2 left, const Vector2& right);
	friend Vector2 operator-(Vector2 left, const Vector2& right);
	friend Vector2 operator*(Vector2 left, const Vector2& right);
	friend Vector2 operator/(Vector2 left, const Vector2& right);

	float Dot(const Vector2& left, const Vector2& right);
};