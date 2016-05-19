#define _USE_MATH_DEFINES
#include<math.h>
#include"Camera.h"
#include"../../glm/glm.hpp"
#include"../../glm/gtc/matrix_transform.hpp"
#include"../../glut.h"

oka::Camera *g_camera = nullptr;

namespace oka
{

	//-------------------------------------
	//�f�t�H���g�R���X�g���N�^

	Camera::Camera():
		m_fovy(60.0),m_aspect(1.0),m_zNear(0.1),m_zFar(1000.0),
		m_position(0.0f, 0.0f, 0.0f),m_target(0.0f, 0.0f, 0.0f),m_up(0.0f, 1.0f, 0.0f)
	{}

	//-------------------------------------
	//

	void Camera::Update()
	{

	}

	//-------------------------------------
	//�����ˉe�s��̓K��

	void Camera::Perspective()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float fov = m_fovy*(M_PI / 180);

		glm::mat4 perspective = glm::perspective(fov, m_aspect, m_zNear, m_zFar);

		glMultMatrixf((GLfloat*)&perspective);
	}

	//-------------------------------------
	//�r���[�s��̐ݒ�

	void Camera::SetViewMatrix(const glm::vec3 _position, const glm::vec3 _target, const glm::vec3 _up)
	{
		m_position = _position;
		m_target = _target;
		m_up = _up;
		
		m_viewMatrix = glm::lookAt(
			glm::vec3(m_position.x, m_position.y, m_position.z),
			glm::vec3(m_target.x, m_target.y, m_target.z),
			glm::vec3(m_up.x, m_up.y, m_up.z));
	}


	//-------------------------------------
	//�r���[�s��̎擾

	glm::mat4 Camera::GetViewMatrix()const
	{
		return m_viewMatrix;
	}


	//-------------------------------------
	//�r���[�s��̓K��
	
	void Camera::MultViewMatrix()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//��ňړ�
		//���C�g�̈ʒu

		float light[] = { 0,1,1, 0 };


		glLightfv(
			GL_LIGHT0,  // GLenum light
			GL_POSITION,// GLenum pname
			light);         // const GLfloat *params

		glMultMatrixf((GLfloat*)&m_viewMatrix);
	}

	//-------------------------------------
	//���ˉe�s��̐ݒ�ƓK��

	void Camera::Ortho(const float _left, const float _right, const float _bottom, const float _top, const float _near, const float _far)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		 glm::mat4 mat = glm::ortho(_left, _right, _bottom, _top, _near, _far);

		glMultMatrixf((GLfloat*)&mat);
	}

}//namespace oka
