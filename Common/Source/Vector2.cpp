#include "Vector2.h"

Vector2::Vector2(float a, float b) : x(a), y(b)
{
}

Vector2::Vector2(const Vector2 &rhs) 
{
	this->x = rhs.x;
	this->y = rhs.y;
}

void Vector2::Set( float a, float b )
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator+( const Vector2& rhs ) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-( const Vector2& rhs ) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator-( void ) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*( float scalar ) const
{
	return Vector2(x * scalar, y * scalar);
}

float Vector2::Length( void ) const
{
	return sqrt(x * x + y * y);
}

float Vector2::Dot( const Vector2& rhs ) const
{
	float ansX = x * rhs.x;
	float ansY = y * rhs.y;
	return ansX + ansY;
}

Vector2 Vector2::Normalized( void )
{
	float length = this->Length();
	x = x / length;
	y = y / length;
	return Vector2();
}
