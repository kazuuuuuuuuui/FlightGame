#define _USE_MATH_DEFINES
#include<math.h>

#include"Bullet.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../glut.h"

void Bullet::Draw()
{
	//glPushAttrib(GL_ALL_ATTRIB_BITS);
	//{
	//	glEnableClientState(GL_VERTEX_ARRAY);
	//	glEnableClientState(GL_NORMAL_ARRAY);

		glPushMatrix();
		{
			//�s��K��
			glMultMatrixf((GLfloat*)&m_transform.m_matrix);

			//glutSolidCube(0.5);
			glutSolidCube(1);

			/*auto v = m_model.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_model.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto i = m_model.m_index.begin();

			glDrawElements(GL_TRIANGLES, m_model.m_indeces * 3, GL_UNSIGNED_SHORT, &(*i));*/

		}
		glPopMatrix();

	//}
	//glPopAttrib();

}

void Bullet::Update()
{
	if (CheckNearCharacter(oka::CharacterManager::GetInstance()->m_characters[1]->m_transform.GetPosition()))
	{
		m_isHorming = false;
	}
	
	//debug
	if (m_isHorming)
	{
		//1���ڂ��ςȕ����ɔ��ł���

		//Homing(oka::CharacterManager::GetInstance()->m_characters[1]->m_transform.GetPosition());
	}

	m_transform.SetPosition(m_transform.GetPosition() + m_speed);

	//�L�����N�^�[�Ƃ̓����蔻��
	unsigned int size = oka::CharacterManager::GetInstance()->m_characters.size();
	for (unsigned int i = 0; i < size; i++)
	{
		glm::vec3 pos = oka::CharacterManager::GetInstance()->m_characters[i]->m_transform.GetPosition();

		if (CheckIsHit(pos))
		{
			oka::CharacterManager::GetInstance()->m_characters[i]->m_isHitAttack = true;
		}
	}

	//debug
	m_transform.Update();
	m_transform.DrawMyToVec();
	//DrawToEnemyVec();

}

bool Bullet::CheckIsHit(glm::vec3 _pos)const
{
	glm::vec3 v;
	v = m_transform.GetPosition() - _pos;

	//�e�ƃL�����N�^�[�Ƃ̋���
	const float value = 2.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;

}


/*

HomingBullet�̕��Ɉڂ�

*/

void Bullet::Homing(glm::vec3 _pos)
{
	//���g�̍��W�ƌ������������̃x�N�g���Ƃ̍���
	glm::vec3 dif = _pos - m_transform.GetPosition();

	//�ړ��̕⊮�l
	static float val = 0.0f;

	dif = dif * val;

	val += 0.0000001f*(M_PI / 180);//�ύX�\��

	if (val >= 1.0f)
	{
		val = 1.0f;
	}

	float x = (m_transform.m_myToVec + dif).x;
	float z = (m_transform.m_myToVec + dif).z;
	float yaw = atan2f(-x, -z);
	m_transform.SetRotationY(yaw);

	float value = 0.005f;//�e�̃X�s�[�h�⊮�l
	m_speed.x = -sin(m_transform.GetRotation().y) * value*(180.0f / M_PI);
	m_speed.y = sin(m_transform.GetRotation().x)* value*(180.0f / M_PI);
	m_speed.z = -cos(m_transform.GetRotation().y) * value*(180.0f / M_PI);

}

bool Bullet::CheckNearCharacter(glm::vec3 _pos)const
{
	glm::vec3 v = _pos - m_transform.GetPosition();
	float distance = glm::length(v);

	const float value = 25.0f;//�e�ƖڕW���̊Ԋu

	if (distance <= value)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//debug

void Bullet::DrawToEnemyVec()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glLineWidth(3.0f);
		glColor3f(1.0f, 0.0f, 1.0f);

		glBegin(GL_LINES);
		{
			glm::vec3 root = m_transform.GetPosition();
			glVertex3f(root.x, root.y, root.z);

			glm::vec3 aim = oka::CharacterManager::GetInstance()->m_characters[1]->m_transform.GetPosition();
			glVertex3f(aim.x, aim.y, aim.z);
		}
		glEnd();
	}
	glPopAttrib();

}