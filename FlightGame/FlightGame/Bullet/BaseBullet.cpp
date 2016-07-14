#include"BaseBullet.h"
#include"../MyLibrary/Manager/FealdManager.h"

//-------------------------------------
//�n�`�������ɂ��邩�O�ɂ��邩�̔���

bool BaseBullet::IsGroundOut()const
{
	//x
	const int width = oka::FealdManager::GetInstance()->m_feald->GetWidth();
	const float x = m_transform.m_position.x;

	if (x <= 0 || width <= x)
	{
		return  true;
	}

	//z
	const int height = oka::FealdManager::GetInstance()->m_feald->GetWidth();
	const float z = m_transform.m_position.z;

	if (z <= -height || 0 <= z)
	{
		return  true;
	}

	return false;
}

//-------------------------------------
//�e�ƒn�`�Ƃ̐ڐG����

bool BaseBullet::IsIntersectGround()const
{
	const int x = (int)m_transform.m_position.x;
	const float y = m_transform.m_position.y;
	const int z = -(int)m_transform.m_position.z;

	const int width = oka::FealdManager::GetInstance()->m_feald->GetWidth();
	const float height = oka::FealdManager::GetInstance()->m_feald->m_vertex[z * width + x].y;

	if (y <= height)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//�C�Ƃ̏Փ˔���
//�C�̊C��(y���W0)��
//���g��y���W�l�Ŕ�r����

bool BaseBullet::IsIntersectSea()const
{
	const float y = m_transform.m_position.y;

	if (y <= 0)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//�e�ƃL�����N�^�[�Ƃ̓����蔻��
//�����Ƃ��ăL�����N�^�[���W��������Ă���

bool BaseBullet::IsHit(glm::vec3 _pos)const
{
	glm::vec3 v;
	v = m_transform.m_position - _pos;

	//�e�ƃL�����N�^�[�Ƃ̋���
	const float value = 5.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;
}