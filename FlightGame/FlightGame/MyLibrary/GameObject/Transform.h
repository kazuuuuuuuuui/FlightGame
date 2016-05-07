#ifndef OKA_TRANSFORM_H_
#define OKA_TRANSFORM_H_

#include"../../glm/mat4x4.hpp"
#include"../../glm/gtc/matrix_transform.hpp"

namespace oka
{
	class Transform
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_lastPosition;
		glm::vec3 m_rotate;//度数管理
		glm::vec3 m_scale;

	public:
		glm::vec3 m_myToVec;//自身の向きベクトル
		glm::vec3 m_myUpVec;//自身の上向きを示すベクトル

		void Update();

		void SetPosition(const glm::vec3 _position) { m_position = _position; }
		void SetPositionX(const float _positionX) { m_position.x = _positionX; }
		void SetPositionY(const float _positionY) { m_position.y = _positionY; }
		void SetPositionZ(const float _positionZ) { m_position.z = _positionZ; }

		void SetRotation(const glm::vec3 _rotate) { m_rotate = _rotate; }
		void SetRotationX(const float _rotateX) { m_rotate.x = _rotateX; }
		void SetRotationY(const float _rotateY) { m_rotate.y = _rotateY; }
		void SetRotationZ(const float _rotateZ) { m_rotate.z = _rotateZ; }

		void SetScale(const glm::vec3 _scale) { m_scale = _scale; }

		glm::vec3 GetPosition()const { return m_position; }
		glm::vec3 GetRotation()const { return m_rotate; }
		glm::vec3 GetScale()const { return m_scale; }

		void SetToVec();
		void SetUpVec();

		//debug用
		void DrawMyToVec();
		void DrawMyUpVec();

	
		Transform() :
			m_position(0.0f, 0.0f, 0.0f),
			m_lastPosition(0.0f, 0.0f, 0.0f),
			m_rotate(0.0f, 0.0f, 0.0f),
			m_scale(1.0f, 1.0f, 1.0f),
			m_myToVec(glm::vec3(0.0f, 0.0f, 0.0f))
		{}
	};

}

extern glm::mat4 BillboardMatrix;

#endif