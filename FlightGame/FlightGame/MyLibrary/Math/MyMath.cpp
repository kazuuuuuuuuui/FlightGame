#define _USE_MATH_DEFINES
#include<math.h>
#include"../../glm/gtc/quaternion.hpp"
#include"../../glm/gtx/quaternion.hpp"
#include"MyMath.h"

namespace oka
{
	//-------------------------------------
	//回転処理
	//クォータニオンから回転行列を作成し返す
	//引数として回転角度と回転軸を受けとる

	glm::tquat<float> MyMath::Rotate(float _angle, glm::vec3 _axis)
	{
		glm::tquat<float> quat;

		quat.x = _axis.x * sin(_angle / 2);
		quat.y = _axis.y * sin(_angle / 2);
		quat.z = _axis.z * sin(_angle / 2);
		quat.w = cos(_angle / 2);

		return quat;
	}

	//-------------------------------------
	//2つのベクトルからクォータニオンを求める

	glm::quat MyMath::RotationBetweenVectors(glm::vec3 start, glm::vec3 dest)
	{
		start = glm::normalize(start);
		dest = glm::normalize(dest);

		glm::vec3 rotationAxis = glm::cross(start, dest);
		float angle = glm::length(rotationAxis);

		//回転軸がないときは何もしない
		if (angle < 0.1f)
		{
			return glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));//何もしないので回転軸は何でもいい
		}

		return glm::angleAxis(angle, glm::normalize(rotationAxis));
	}
}