#ifndef OKA_TRANSFORM_H_
#define OKA_TRANSFORM_H_

#include"../../glm/gtc/matrix_transform.hpp"
#include"../../glm/gtc/quaternion.hpp"

namespace oka
{
	class Transform
	{
	public:
		glm::mat4 m_matrix;
		glm::vec3 m_position;
		glm::tquat<float> m_rotate;
		glm::vec3 m_scale;
		glm::vec3 m_myToVec;//���g�̌����x�N�g��
		glm::vec3 m_myUpVec;//���g�̏�����������x�N�g��
		glm::vec3 m_mySideVec;//���g�̉������������x�N�g��

		void Update();
		void SetAimVec(glm::vec3 &_myVec, const glm::vec3 _aimVec);
		Transform();
	};

}

extern glm::mat4 BillboardMatrix;

#endif