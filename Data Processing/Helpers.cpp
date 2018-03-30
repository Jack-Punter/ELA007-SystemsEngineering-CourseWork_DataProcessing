#include "Helpers.h"

std::ostream& operator<<(std::ostream& cout, const Matrix2D& rhs)
{
	return cout << '\n' << rhs.r0c0 << "  " << rhs.r0c1 << '\n' << rhs.r1c0 << "  " << rhs.r1c1;
}

std::ostream& operator<<(std::ostream& cout, const Vec2& rhs)
{
	return cout << " {x: " << rhs.GetX() << " y: " << rhs.GetY() << " }";
}

std::ostream& operator<<(std::ostream& cout, const outputData& rhs)
{
	return cout << " {Location: " << rhs.loc << " Time: " << rhs.time << " }";
}

