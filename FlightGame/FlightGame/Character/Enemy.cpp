#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"
#include"../glut.h"

//debug
#include"../MyLibrary/Manager/CharacterManager.h"

//-------------------------------------
//�G��AI

void Enemy::Control()
{
	MoveToAimPos();
	//SetYaw();
	//SetPitch();

	m_value += 0.00001f*(M_PI / 180);//�ύX�\��

	if (m_value >= 1.0f)
	{
		m_value = 1.0f;
	}

	//�����H
	if (CheckNearAimPis())
	{
		ResetAimPos();
	}

	//debug
	//DrawAimPos();
	//DrawToAimVec();
}

//-------------------------------------
//��_���W�����߂Ă����Ɍ������Ĉړ�����

void Enemy::MoveToAimPos()
{	
	//�����̍��W����ڕW�_�ւ̌����x�N�g��
	glm::vec3 vec = m_aimPos - m_transform.GetPosition();
	vec = glm::normalize(vec);

	//�X�s�[�h�̐ݒ�
	m_speed = vec*0.2f;

}

//-------------------------------------
//���[��]����

void Enemy::SetYaw()
{
	//���g�̍��W�ƌ������������̃x�N�g���Ƃ̍���
	glm::vec3 dif = m_aimPos - m_transform.GetPosition();

	//�ړ��̕⊮�l

	dif = dif * m_value;

	float x = (m_transform.m_myToVec + dif).x;
	float z = (m_transform.m_myToVec + dif).z;
	float yaw = atan2f(-x, -z);
	m_transform.SetRotationY(yaw);

}

//-------------------------------------
//�s�b�`��]����

void Enemy::SetPitch()
{
	//�����x�N�g���ƌ������������̃x�N�g���Ƃ̍���
	glm::vec3 dif = - m_transform.GetPosition();

	//�ړ��̕⊮�l

	dif = dif * m_value;

	float y = (m_transform.m_myToVec + dif).y;
	float z = (m_transform.m_myToVec + dif).z;
	float pitch = atan2f(-y, -z);
	m_transform.SetRotationX(pitch);

}

//-------------------------------------
//�ڕW�_�Ǝ��g�̋��������l�ȓ��Ȃ�true
//���l�O�ł����false��Ԃ�

bool Enemy::CheckNearAimPis()const
{
	glm::vec3 v;
	v = m_aimPos - m_transform.GetPosition();

	//�����̈��l
	const float value = 5.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//�ڕW�_�̍Đݒ�

void Enemy::ResetAimPos()
{
	const float x_max = 256.0f;
	m_aimPos.x = ((float)rand() / RAND_MAX)*x_max;

	const float bottom = 5.0f;
	m_aimPos.y = bottom + ((float)rand() / RAND_MAX)*10.0f;

	const float z_max = -256.0f;
	m_aimPos.z = ((float)rand() / RAND_MAX)*z_max;
}


//-------------------------------------
//debug

//-------------------------------------
//�ڎw���Ă�����W�_����

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
//�ڎw���Ă�����W�_�ւ̕����x�N�g������

void Enemy::DrawToAimVec()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glLineWidth(3.0f);
		glColor3f(1.0f, 1.0f, 0.0f);

		glBegin(GL_LINES);
		{
			glm::vec3 root = m_transform.GetPosition();
			glVertex3f(root.x, root.y, root.z);

			glm::vec3 aim = m_aimPos;
			glVertex3f(aim.x, aim.y, aim.z);
		}
		glEnd();
	}
	glPopAttrib();
}