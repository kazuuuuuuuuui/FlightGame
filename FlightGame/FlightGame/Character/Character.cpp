#define _USE_MATH_DEFINES
#include<math.h>
#include"Character.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Screen/Screen.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/FealdManager.h"
#include"../glut.h"


//-------------------------------------
//�R���X�g���N�^

Character::Character()
{
	m_transform.m_scale = glm::vec3(2.0f, 2.0f, 2.0f);

	oka::ModelSP body = oka::ModelManager::GetInstance()->GetModel("Body");
	unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("FlyTex"));

	m_body = oka::Mesh::Create(body, tex);
	oka::GameManager::GetInstance()->Add("Body", m_body);

	m_onRadarPos = glm::vec2(0.0f, 0.0f);

	m_isHitAttack = false;

	m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
};

//-------------------------------------
//�U�����󂯂Ă��邩�̃t���O��ω�������

void Character::SetIsHitAttack(bool _isHitAttack)
{
	m_isHitAttack = _isHitAttack;
}

//-------------------------------------
//�U�����󂯂Ă��邩�̃t���O��Ԃ�

bool Character::GetIsHitAttack()const
{
	return m_isHitAttack;
}

//-------------------------------------
//�G����łǂ��Ɉʒu���Ă��邩�v�Z����

void Character::SetOnRadarPos()
{
	static const float radarWidth = oka::Screen::GetInstance()->GetWidth() / 3.0f;
	static const float radarHeight = oka::Screen::GetInstance()->GetHeight() / 3.0f;

	static const float left = oka::FealdManager::GetInstance()->m_feald->m_leftBottom.x;
	static const float right = oka::FealdManager::GetInstance()->m_feald->m_rightBottom.x;
	static const float bottom = oka::FealdManager::GetInstance()->m_feald->m_leftBottom.z;
	static const float top = oka::FealdManager::GetInstance()->m_feald->m_rightTop.z;

	m_onRadarPos.x = (m_transform.m_position.x + abs(left))*(radarWidth / (abs(left) + (abs(right))));
	m_onRadarPos.y = ((m_transform.m_position.z - abs(bottom))*(radarHeight / -(abs(top) + abs(bottom))));
}

//-------------------------------------
//�G����łǂ��Ɉʒu���Ă��邩�`�悷��

void Character::DrawRadarPos()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glColor3f(1, 0, 0);
		glPointSize(10);

		glBegin(GL_POINTS);
		{
			glVertex2f(m_onRadarPos.x, m_onRadarPos.y);
		}
		glEnd();
	}
	glPopAttrib();
}

//-------------------------------------
//�t�B�[���h���̊���̈ړ��\�͈͂���
//�o�Ă��Ȃ����̔���

//bool Character::IsFealdOut()const
//{
//
//
//	return false;
//}


//-------------------------------------
//�n�`�������ɂ��邩�O�ɂ��邩�̔���

bool Character::IsGroundOut()const
{
	//x
	const float width = oka::FealdManager::GetInstance()->m_feald->GetWidth();
	const float x = m_transform.m_position.x;

	if (x < 0 || width < x)
	{
		return  true;
	}

	//z
	const float height = oka::FealdManager::GetInstance()->m_feald->GetDepth();
	const float z = m_transform.m_position.z;

	if (z < -height || 0 < z)
	{
		return  true;
	}

	return false;
}

//-------------------------------------
//�t�B�[���h�Ƃ̏Փ˔���
//�e�t�B�[���h���_��y���W�l��
//���g��y���W�l�Ŕ�r����

bool Character::IsIntersectGround()const
{
	const int x = m_transform.m_position.x;
	const float y = m_transform.m_position.y;
	const int z = -m_transform.m_position.z;

	const int width = oka::FealdManager::GetInstance()->m_feald->GetWidth();

	const float height = oka::FealdManager::GetInstance()->m_feald->m_vertex[z * width + x].y;

	if ( y <= height)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//�C�Ƃ̏Փ˔���
//�C�̊C��(y���W0)��
//���g��y���W�l�Ŕ�r����

bool Character::IsIntersectSea()const
{
	const float y = m_transform.m_position.y;

	if (y <=0)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//������͈͓��Ɉ����̍��W�����݂��邩�𔻕ʂ���

bool Character::IsNear(glm::vec3 _pos,float _distance)const
{
	const glm::vec3 pos = _pos - m_transform.m_position;
	const float distance = glm::length(pos);

	if (0.0f == distance)
	{
		return false;
	}
	else if (distance < _distance)
	{
		return true;
	}

	return false;
}

