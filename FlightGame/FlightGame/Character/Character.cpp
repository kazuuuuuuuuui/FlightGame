#define _USE_MATH_DEFINES
#include<math.h>
#include"Character.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"

#include"../glut.h"

void Character::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			//�s��K��
			glMultMatrixf((GLfloat*)&m_transform.m_matrix);

			//glutSolidTeapot(1);
		}
		glPopMatrix();
	}
	glPopAttrib();

	/*glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glPushMatrix();
		{
			glMultMatrixf((GLfloat*)&m_matrix);

			auto v = m_body->m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_body->m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto i = m_body->m_index.begin();

			glDrawElements(GL_TRIANGLES, m_indeces * 3, GL_UNSIGNED_SHORT, &(*i));

		}
		glPopMatrix();

	}
	glPopAttrib();*/

}

void Character::Update()
{
	if (m_isHitAttack)
	{
		//��������
		m_hp -= 5;
	}

	m_isHitAttack = false;

	//���W�X�V
	m_speed += m_accel;
	m_transform.SetPosition(m_transform.GetPosition() + m_speed);

	//����
	m_speed *= 0.965f;

	//���S����
	if (CheckIsDead())
	{
		m_isActive = false;

		//�����G�t�F�N�g
		/*oka::GameManager::GetInstance()->AddGameObject("Smoke", Smoke::Create(m_transform.GetPosition()));
		oka::GameManager::GetInstance()->AddGameObject("Fire", Fire::Create(m_transform.GetPosition()));*/
	}


	//debug
	m_transform.DrawMyToVec();
	m_transform.DrawMyUpVec();
	m_transform.DrawMySideVec();
}

//-------------------------------------
//HP�̒l���Q�Ƃ�0�ȉ��ɂȂ��Ă����true
//�����łȂ����false��Ԃ�

bool Character::CheckIsDead()const
{
	if (m_hp <= 0)
	{	
		return true;
	}

	return false;
	
}
