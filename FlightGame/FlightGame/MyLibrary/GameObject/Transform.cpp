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

		SetAimVec(m_myToVec, glm::vec3(0, 0, -1));
		SetAimVec(m_myUpVec, glm::vec3(0, 1, 0));
		SetAimVec(m_mySideVec, glm::vec3(1, 0, 0));

	}

	//ܰ��ޏ�̃x�N�g�� = ���W�s�� * ��]�s��
	//(�����x�N�g��) = ( 0,0,-1 ) * ( �I�u�W�F�N�g�̉�]�݂̂̍s�� )

	void Transform::SetAimVec(glm::vec3 &_myVec, const glm::vec3 _aimVec)
	{
		//���W�s��
		glm::mat4 pos;
		pos[3][0] = _aimVec.x;
		pos[3][1] = _aimVec.y;
		pos[3][2] = _aimVec.z;

		//�����x�N�g�������߂邽�߂̍s��
		glm::mat4 mat;
		mat = m_rotateMatrix*pos;

		_myVec.x = mat[3][0];
		_myVec.y = mat[3][1];
		_myVec.z = mat[3][2];

		//���K��
		_myVec = (_myVec / glm::length(_myVec));
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
				aim.x = root.x + m_myToVec.x;
				aim.y = root.y + m_myToVec.y;
				aim.z = root.z + m_myToVec.z;

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
				aim.x = root.x + m_myUpVec.x;
				aim.y = root.y + m_myUpVec.y;
				aim.z = root.z + m_myUpVec.z;

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
				aim.x = root.x + m_mySideVec.x;
				aim.y = root.y + m_mySideVec.y;
				aim.z = root.z + m_mySideVec.z;

				glVertex3f(aim.x, aim.y, aim.z);
			}
			glEnd();
		}
		glPopAttrib();

	}
}