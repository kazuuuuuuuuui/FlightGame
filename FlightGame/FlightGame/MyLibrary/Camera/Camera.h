#ifndef _OKA_CAMERA_H_
#define _OKA_CAMERA_H_

#include"../GameObject/Transform.h"
#include"../../glm/mat4x4.hpp"

namespace oka 
{
	class Camera
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_target;
		glm::vec3 m_up;
		glm::mat4 m_viewMatrix;
		float m_fovy;//ìxêî Ç≈ä«óù
		float m_aspect;
		float m_zNear;
		float m_zFar;

	public:
		Camera();
		~Camera() {};

		void Update();
		void Perspective();
		void SetViewMatrix(const glm::vec3 _eye,const glm::vec3 _target,const glm::vec3 _up);
		void MultViewMatrix();
		void Ortho(const float _left, const float _right, const float _bottom, const float _top, const float _near, const float _far);

		glm::mat4 GetViewMatrix()const;	
	};

}//namespace oka

extern oka::Camera *g_camera;

#endif

