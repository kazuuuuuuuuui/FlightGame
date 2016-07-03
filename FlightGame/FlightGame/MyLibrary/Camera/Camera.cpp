#include"Camera.h"
#include"../Math/MyMath.h"
#include"../../glut.h"

oka::Camera *g_camera = nullptr;

namespace oka
{

	//-------------------------------------
	//デフォルトコンストラクタ

	Camera::Camera():
		m_fovy(60.0f),m_aspect(1.0f),m_zNear(0.1f),m_zFar(1000.0f),
		m_position(glm::vec3(0.0f, 0.0f, 0.0f)),m_target(glm::vec3(0.0f, 0.0f, 0.0f)),m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
		m_viewMatrix(glm::mat4(1.0f))
	{}

	//-------------------------------------
	//

	void Camera::SetPos(glm::vec3 _pos)
	{
		m_position = _pos;
	}

	//-------------------------------------
	//

	void Camera::SetTarget(glm::vec3 _target)
	{
		m_target = _target;
	}

	//-------------------------------------
	//

	void Camera::SetUp(glm::vec3 _up)
	{
		m_up = _up;
	}

	glm::vec3 Camera::GetUp()const
	{
		return m_up;
	}

	//-------------------------------------
	//透視射影行列の適応

	void Camera::Perspective()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float fov = oka::MyMath::ToRadian(m_fovy);

		glm::mat4 mat = glm::perspective(fov, m_aspect, m_zNear, m_zFar);

		glMultMatrixf((GLfloat*)&mat);
	}

	//-------------------------------------
	//ビュー行列の設定

	void Camera::SetViewMatrix()
	{
		m_viewMatrix = glm::lookAt(
			glm::vec3(m_position.x, m_position.y, m_position.z),
			glm::vec3(m_target.x, m_target.y, m_target.z),
			glm::vec3(m_up.x, m_up.y, m_up.z));
	}

	//-------------------------------------
	//ビュー行列の取得

	glm::mat4 Camera::GetViewMatrix()const
	{
		return m_viewMatrix;
	}


	//-------------------------------------
	//ビュー行列の適応
	
	void Camera::MultViewMatrix()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMultMatrixf((GLfloat*)&m_viewMatrix);
	}

	//-------------------------------------
	//射影行列の設定と適応

	void Camera::Ortho(const float _left, const float _right, const float _bottom, const float _top, const float _near, const float _far)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//後で移動
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		 glm::mat4 mat = glm::ortho(_left, _right, _bottom, _top, _near, _far);

		glMultMatrixf((GLfloat*)&mat);
	}

}//namespace oka
