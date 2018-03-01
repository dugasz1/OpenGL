#ifndef MATH_HPP
#define MATH_HPP
#include <iostream>
#include <math.h>
#include "glm\glm.hpp"

namespace math {
	const double M_PI = 3.14159265359;
	

	double degreeToRadian(double degree);
	float sign(glm::fvec3& p1, glm::fvec3& p2, glm::fvec3& p3);
	bool isPointInTriangle2D(glm::fvec3& pt, glm::fvec3& v1, glm::fvec3& v2, glm::fvec3& v3);
}

#endif // !MATHEMATICS_HPP
