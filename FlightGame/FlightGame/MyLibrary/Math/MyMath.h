#ifndef OKA_MYMATH_H_
#define OKA_MYMATH_H_

namespace oka
{
	class MyMath 
	{
	public:
		static float ToRadian(const float _degree);
		static glm::tquat<float> Rotate(float _angle, glm::vec3 _axis);
	};
}

#endif