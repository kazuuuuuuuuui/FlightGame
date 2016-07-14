#ifndef OKA_MYMATH_H_
#define OKA_MYMATH_H_

namespace oka
{
	class MyMath 
	{
	public:
		static glm::tquat<float> Rotate(float _angle, glm::vec3 _axis);
		static glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);

	};
}

#endif