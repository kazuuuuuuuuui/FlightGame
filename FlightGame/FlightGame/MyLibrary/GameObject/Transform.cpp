#include<stdio.h>
#include"Transform.h"
#include"../Camera/Camera.h"
#include"../../glm/gtc/quaternion.hpp"
#include"../../glm/gtx/quaternion.hpp"
#include"../../glm/gtx/transform.hpp"
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
		glm::mat4 translate = glm::translate(m_position);

		glm::mat4 rotate = glm::toMat4(m_rotate);

		//scale
		glm::mat4 scale = glm::scale(m_scale);

		m_matrix = translate * rotate * scale;

		SetAimVec(m_myToVec, glm::vec3(0, 0, -1));
		SetAimVec(m_myUpVec, glm::vec3(0, 1, 0));
		SetAimVec(m_mySideVec, glm::vec3(1, 0, 0));


		//debug
		/*DrawMyToVec();
		DrawMyUpVec();
		DrawMySideVec();*/

	}

	//ܰ��ޏ�̃x�N�g�� = ���W�s�� * ��]�s��
	//(�����x�N�g��) = ( 0,0,-1 ) * ( �I�u�W�F�N�g�̉�]�݂̂̍s�� )

	void Transform::SetAimVec(glm::vec3 &_myVec, const glm::vec3 _aimVec)
	{
		//���W�s��
		glm::mat4 pos;
		pos = glm::translate(_aimVec);

		glm::mat4 rot = glm::toMat4(m_rotate);

		//�����x�N�g�������߂邽�߂̍s��
		glm::mat4 mat;
		mat = rot*pos;

		_myVec.x = mat[3][0];
		_myVec.y = mat[3][1];
		_myVec.z = mat[3][2];

		_myVec = glm::normalize(_myVec);
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
				glm::vec3 root = m_position;
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
				glm::vec3 root = m_position;
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
				glm::vec3 root = m_position;
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