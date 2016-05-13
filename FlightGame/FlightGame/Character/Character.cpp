#define _USE_MATH_DEFINES
#include<math.h>
#include"Character.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"

#include"../glut.h"

//-------------------------------------
//�R���X�g���N�^

Character::Character()
{
	m_controller = new oka::Contoroller();
	oka::JoysticManager::GetInstance()->AddController(m_controller);

	m_isHitAttack = false;
	m_hp = 100;
	m_speed=glm::vec3(0.0f, 0.0f, 0.0f);
	m_accel=glm::vec3(0.0f, 0.0f, 0.0f);
};



//-------------------------------------
//���g�̕`��
//���f���}�l�[�W���[���烂�f���f�[�^���Q�Ƃ���

void Character::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			//�s��K��
			glMultMatrixf((GLfloat*)&m_transform.m_matrix);

			glutSolidTeapot(1);
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
	//m_controller->Update();

	if (m_controller->CheckIsConect())
	{
		unsigned short pressedKey = m_controller->m_state.Gamepad.wButtons;
		unsigned int downKeys = m_controller->m_downkey;
		float sThumbLX = m_controller->m_sThumbLX;
		float sThumbLY = m_controller->m_sThumbLY;

		Control(pressedKey, downKeys, sThumbLX, sThumbLY);
	}
	else
	{
			//Control();
	}
	


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
	if (m_isActive)
	{
		if (CheckIsDead())
		{
			m_isActive = false;

			//�����G�t�F�N�g
			const unsigned int num = 20;
			oka::GameManager::GetInstance()->AddGameObject("Smoke", Smoke::Create(m_transform.GetPosition(), num));
			oka::GameManager::GetInstance()->AddGameObject("Fire", Fire::Create(m_transform.GetPosition()));
		}
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
