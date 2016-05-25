#ifndef OKA_TRANSFORM_H_
#define OKA_TRANSFORM_H_

#include"../../glm/mat4x4.hpp"
#include"../../glm/gtc/matrix_transform.hpp"

namespace oka
{
	class Transform
	{
	public:
		glm::mat4 m_matrix;
		glm::vec3 m_position;
		glm::mat4 m_rotate;
		glm::vec3 m_scale;

		glm::vec3 m_myToVec;//自身の向きベクトル
		glm::vec3 m_myUpVec;//自身の上向きを示すベクトル
		glm::vec3 m_mySideVec;//自身の横向きを示すベクトル

		void Update();

		void SetAimVec(glm::vec3 &_myVec, const glm::vec3 _aimVec);

		//debug用
		void DrawMyToVec();
		void DrawMyUpVec();
		void DrawMySideVec();
	
		Transform() :
			m_matrix(glm::mat4(1.0f)),
			m_position(0.0f, 0.0f, 0.0f),
			m_rotate(glm::mat4(1.0f)),
			m_scale(1.0f, 1.0f, 1.0f),
			m_myToVec(glm::vec3(0.0f, 0.0f, -1.0f)),
			m_myUpVec(glm::vec3(0.0f, 1.0f, 0.0f)),
			m_mySideVec(glm::vec3(1.0f, 0.0f, 0.0f))
		{}
	};

}

extern glm::mat4 BillboardMatrix;

#endif