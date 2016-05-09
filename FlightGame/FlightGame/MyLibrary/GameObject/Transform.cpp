#include"Transform.h"
#include"../../glut.h"

glm::mat4 BillboardMatrix;

namespace oka
{
	void Transform::Update()
	{
		SetToVec();
	}

	//-------------------------------------
	//自身の向きベクトルの計算

	void Transform::SetToVec()
	{
		m_myToVec.x = -sin(GetRotation().y);
		m_myToVec.y = sin(GetRotation().x);
		m_myToVec.z = -cos(GetRotation().y);
	}

	//-------------------------------------
	//自身の上向きベクトルの計算

	void Transform::SetUpVec()
	{



	}

	//-------------------------------------
	//debug用

	//-------------------------------------
	//進行方向のベクトル可視化

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
	//進行方向に対して垂直上向きのベクトル可視化

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
				aim.x = root.x;
				aim.z = root.z;

				aim.y = root.y;

				glVertex3f(aim.x, aim.y, aim.z);
			}
			glEnd();
		}
		glPopAttrib();
	}

}