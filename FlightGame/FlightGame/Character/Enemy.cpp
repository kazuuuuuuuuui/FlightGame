#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"
#include"../glm/gtx/transform.hpp"
#include"../glut.h"

//-------------------------------------
//敵のAI

void Enemy::Control()
{
	m_speed.z = -0.1f;

	
	/*glm::vec3 v = m_aimPos - m_transform.m_position;

	if (glm::length(v) <= 5.0f)
	{
		ResetAimPos();
	}

	v = glm::normalize(v);
	v *= 0.01f;
	m_accel = v;*/

	

//printf("x:%f,y:%f,z:%f\n", m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z);

	//debug
	DrawAimPos();
}

//-------------------------------------
//目標点の再設定

void Enemy::ResetAimPos()
{
	const float x_max = 256.0f;
	m_aimPos.x = ((float)rand() / RAND_MAX)*x_max;

	const float bottom = 20.0f;
	m_aimPos.y = bottom + ((float)rand() / RAND_MAX)*10.0f;

	const float z_max = -256.0f;
	m_aimPos.z = ((float)rand() / RAND_MAX)*z_max;
}


//-------------------------------------
//debug

//-------------------------------------
//目指している座標点可視化

void Enemy::DrawAimPos()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glColor3f(1.0f, 0.0f, 0.0f);

		glPushMatrix();
		{
			glTranslatef(m_aimPos.x, m_aimPos.y, m_aimPos.z);
			glutSolidCube(1);
		}
		glPopMatrix();

	}
	glPopAttrib();
}

//-------------------------------------
//目指している座標点への方向ベクトル可視化

void Enemy::DrawToAimVec()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glLineWidth(3.0f);
		glColor3f(1.0f, 1.0f, 0.0f);

		glBegin(GL_LINES);
		{
			glm::vec3 root = m_transform.m_position;
			glVertex3f(root.x, root.y, root.z);

			glm::vec3 aim = m_aimPos;
			glVertex3f(aim.x, aim.y, aim.z);
		}
		glEnd();
	}
	glPopAttrib();
}