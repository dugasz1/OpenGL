#include "Math.hpp"

namespace math {
	double degreeToRadian(double degree)
	{
		return degree * M_PI / 180.0;
	}

	float sign(glm::fvec3& p1, glm::fvec3& p2, glm::fvec3& p3)
	{
		return (p1.x - p3.x) * (p2.z - p3.z) - (p2.x - p3.x) * (p1.z - p3.z);
	}

	bool isPointInTriangle2D(glm::fvec3& pt, glm::fvec3& v1, glm::fvec3& v2, glm::fvec3& v3)
	{
		bool b1, b2, b3;

		b1 = sign(pt, v1, v2) < 0.0f;
		b2 = sign(pt, v2, v3) < 0.0f;
		b3 = sign(pt, v3, v1) < 0.0f;

		//std::cout << b1 << " | " << b2 << " | " << b3 << std::endl;

		return ((b1 == b2) && (b2 == b3));
	}

}