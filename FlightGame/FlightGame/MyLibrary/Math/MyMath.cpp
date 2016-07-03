#define _USE_MATH_DEFINES
#include<math.h>

#include"../../glm/gtc/quaternion.hpp"
#include"../../glm/gtx/quaternion.hpp"

#include"MyMath.h"

namespace oka
{
	float MyMath::ToRadian(const float _degree)
	{
		return _degree*((float)M_PI / 180.0f);
	}

	//-------------------------------------
	//回転処理
	//クォータニオンから回転行列を作成し返す
	//引数として回転角度と回転軸を受けとる

	glm::tquat<float> MyMath::Rotate(float _angle, glm::vec3 _axis)
	{
		//glm::mat4 mat;
		glm::tquat<float> quat;

		quat.x = _axis.x * sin(_angle / 2);
		quat.y = _axis.y * sin(_angle / 2);
		quat.z = _axis.z * sin(_angle / 2);
		quat.w = cos(_angle / 2);

		//quat = glm::quat(quat);
		//mat = glm::toMat4(quat);

		return quat;
	}


}