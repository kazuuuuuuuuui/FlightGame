#ifndef CAMERA_H_
#define CAMERA_H_

#include<memory>
#include"../GameObject/Transform.h"

namespace oka 
{
	class Camera;
	typedef std::shared_ptr<Camera> CameraSP;

	class Camera
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_target;
		glm::vec3 m_up;
		glm::mat4 m_viewMatrix;
		float m_fovy;
		float m_aspect;
		float m_zNear;
		float m_zFar;

	public:
		Camera();
		~Camera() {};

		void SetPos(glm::vec3 _pos);
		void SetTarget(glm::vec3 _target);
		void SetUp(glm::vec3 _up);
		glm::vec3 GetUp()const;
		void Perspective();
		void SetViewMatrix();
		void MultViewMatrix();
		void Ortho(const float _left, const float _right, const float _bottom, const float _top, const float _near, const float _far);
		glm::mat4 GetViewMatrix()const;	
	};

}//namespace oka

extern oka::Camera *g_camera;

#endif

