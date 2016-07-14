#define _USE_MATH_DEFINES
#include<math.h>
#include"../../glm/gtc/quaternion.hpp"
#include"../../glm/gtx/quaternion.hpp"
#include"MyMath.h"

namespace oka
{
	//-------------------------------------
	//��]����
	//�N�H�[�^�j�I�������]�s����쐬���Ԃ�
	//�����Ƃ��ĉ�]�p�x�Ɖ�]�����󂯂Ƃ�

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
	//2�̃x�N�g������N�H�[�^�j�I�������߂�

	glm::quat MyMath::RotationBetweenVectors(glm::vec3 start, glm::vec3 dest)
	{
		start = glm::normalize(start);
		dest = glm::normalize(dest);

		glm::vec3 rotationAxis = glm::cross(start, dest);
		float angle = glm::length(rotationAxis);

		//��]�����Ȃ��Ƃ��͉������Ȃ�
		if (angle < 0.1f)
		{
			return glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));//�������Ȃ��̂ŉ�]���͉��ł�����
		}

		return glm::angleAxis(angle, glm::normalize(rotationAxis));
	}
}