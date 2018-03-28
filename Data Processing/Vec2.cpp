#include "Vec2.h"

Vec2::Vec2(double x, double y)
	:
	x(x),
	y(y)
{}

Vec2 Vec2::operator+(const Vec2& lhs) const
{
	return { x + lhs.x, y + lhs.y };
}

Vec2 Vec2::operator-(const Vec2& lhs) const
{
	return { x - lhs.x, y - lhs.y };
}

double Vec2::GetX() const
{
	return x;
}

double Vec2::GetY() const
{
	return y;
}

Vec2 operator*(double rhs, const Vec2& lhs)
{
	return { rhs * lhs.GetX(), rhs * lhs.GetY() };
}