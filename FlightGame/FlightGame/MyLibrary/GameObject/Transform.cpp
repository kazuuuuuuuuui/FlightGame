#include<stdio.h>
#include"Transform.h"
#include"../Camera/Camera.h"
#include"../../glut.h"

glm::mat4 BillboardMatrix;

namespace oka
{
	void Transform::Update()
	{
		//�s��v�Z
		BillboardMatrix = glm::inverse(g_camera->GetViewMatrix());
		BillboardMatrix[3][0] = 0;
		BillboardMatrix[3][1] = 0;
		BillboardMatrix[3][2] = 0;

		//translate
		m_translateMatrix = glm::mat4(1.0f);
		m_translateMatrix = glm::translate(m_translateMatrix, GetPosition());

		//scale
		m_scaleMatrix = glm::mat4(1.0f);
		m_scaleMatrix = glm::scale(m_scaleMatrix, GetScale());

		//�s���Z
		m_matrix = glm::mat4(1.0f);
		m_matrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;

		SetToVec();
		SetUpVec();
		SetSideVec();
	}

	//-------------------------------------
	//���g�̌����x�N�g���̌v�Z

	void Transform::SetToVec()
	{
		m_myToVec.x = -sin(GetRotation().y);
		m_myToVec.y = sin(GetRotation().x);
		m_myToVec.z = -cos(GetRotation().y);

		m_myToVec = glm::normalize(m_myToVec);

		//debug
printf("x:%f", m_myToVec.x);
printf(" y:%f", m_myToVec.y);
printf(" z:%f\n", m_myToVec.z);

	}

	//-------------------------------------
	//���g�̏�����x�N�g���̌v�Z

	void Transform::SetUpVec()
	{
		glm::mat4 mat;
		glm::mat4 up;
		up = glm::translate(up, glm::vec3(0, 1, 0));

		mat = m_rotateMatrix * up;

		m_myUpVec.x = mat[3][0];
		m_myUpVec.y = mat[3][1];
		m_myUpVec.z = mat[3][2];

		m_myUpVec = glm::normalize(m_myUpVec);

//debug
//printf("x:%f", m_myUpVec.x);
//printf(" y:%f", m_myUpVec.y);
//printf(" z:%f\n", m_myUpVec.z);

	}

	//-------------------------------------
	//���g�̉������̃x�N�g���v�Z

	void Transform::SetSideVec()
	{		
		m_mySideVec = glm::cross(m_myToVec, m_myUpVec);
		m_mySideVec = glm::normalize(m_mySideVec);
	}

	//-------------------------------------
	//debug�p

	//-------------------------------------
	//�i�s�����̃x�N�g������

	void Transform::DrawMyToVec()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			glDisable(GL_LIGHTING);

			glLineWidth(3.0f);
			glColor3f(1.0f, 0.0f, 0.0f);

			glBegin(GL_LINES);
			{
				glm::vec3 root = GetPosition();
				glVertex3f(root.x, root.y, root.z);

				glm::vec3 aim;
				aim.x = root.x + m_myToVec.x * 8;
				aim.y = root.y + m_myToVec.y * 8;
				aim.z = root.z + m_myToVec.z * 8;

				glVertex3f(aim.x, aim.y, aim.z);
			}
			glEnd();
		}
		glPopAttrib();
	}

	//-------------------------------------
	//�i�s�����ɑ΂��Đ���������̃x�N�g������

	void Transform::DrawMyUpVec()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			glDisable(GL_LIGHTING);

			glLineWidth(3.0f);
			glColor3f(0.0f, 1.0f, 0.0f);

			glBegin(GL_LINES);
			{
				glm::vec3 root = GetPosition();
				glVertex3f(root.x, root.y, root.z);

				glm::vec3 aim;
				aim.x = root.x + m_myUpVec.x * 3;
				aim.y = root.y + m_myUpVec.y * 3;
				aim.z = root.z + m_myUpVec.z * 3;

				glVertex3f(aim.x, aim.y, aim.z);
			}
			glEnd();
		}
		glPopAttrib();

	}

	//-------------------------------------
	//�i�s�����ɑ΂��Đ����������̃x�N�g������

	void Transform::DrawMySideVec()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			glDisable(GL_LIGHTING);

			glLineWidth(3.0f);
			glColor3f(1.0f, 1.0f, 0.0f);

			glBegin(GL_LINES);
			{
				glm::vec3 root = GetPosition();
				glVertex3f(root.x, root.y, root.z);

				glm::vec3 aim;
				aim.x = root.x + m_mySideVec.x * 3;
				aim.y = root.y + m_mySideVec.y * 3;
				aim.z = root.z + m_mySideVec.z * 3;

				glVertex3f(aim.x, aim.y, aim.z);
			}
			glEnd();
		}
		glPopAttrib();

	}
}