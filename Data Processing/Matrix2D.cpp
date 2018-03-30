#include <math.h>
#include "Matrix2D.h"
#define PI 3.14159265358979323846

Matrix2D::Matrix2D(double r0c0, double r0c1, double r1c0, double r1c1)
	:
	r0c0(r0c0),
	r0c1(r0c1),
	r1c0(r1c0),
	r1c1(r1c1)
{}

Vec2 Matrix2D::operator*(const Vec2& lhs) const
{
	return { r0c0 * lhs.GetX() + r0c1 * lhs.GetY(),
			 r1c0 * lhs.GetX() + r1c1 * lhs.GetY() };
}


Matrix2D Matrix2D::operator*(const Matrix2D& lhs) const
{
	return { r0c0 * lhs.r0c0 + r0c1 * lhs.r1c0, r0c0 * lhs.r0c1 + r0c1 * lhs.r1c1,
			 r1c0 * lhs.r0c0 + r1c1 * lhs.r1c0, r1c0 * lhs.r0c1 + r1c1 * lhs.r1c1 };
}

double Matrix2D::Det() const
{
	return r0c0 * r1c1 - r1c0 * r0c1;
}

Matrix2D Matrix2D::Inverse() const
{
	return 1.0 / Det() * Matrix2D(r1c1, -r0c1, -r1c0, r0c0);
}

Matrix2D Matrix2D::Rotation(double angle)
{
	double theta = angle * PI / 180.0;

	double c = cos(theta);
	double s = sin(theta);

	return { c, s,
			-s, c };
}

Matrix2D operator*(double lhs, const Matrix2D& rhs)
{
	return { lhs * rhs.r0c0, lhs * rhs.r0c1, lhs * rhs.r1c0, lhs * rhs.r1c1 };
}