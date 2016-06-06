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
//#include"../MyLibrary/Input/Keyboard.h"
//#include"Player.h"
#include"../glut.h"


//-------------------------------------
//�R���X�g���N�^

Character::Character()
{
	m_transform.m_scale = glm::vec3(0.3f, 0.6f, 0.3f);
	m_onRadarPos = glm::vec2(0.0f, 0.0f);

	//�̕���
	oka::ModelSP body = oka::ModelManager::GetInstance()->m_models["Body"];
	unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("FlyTex"));
	m_body = oka::Mesh::Create(body, tex);
	oka::GameManager::GetInstance()->Add("Body", m_body);

	//�v���y������
	oka::ModelSP propeller = oka::ModelManager::GetInstance()->m_models["Propeller"];
	m_propeller = oka::Mesh::Create(propeller, tex);
	oka::GameManager::GetInstance()->Add("Propeller", m_propeller);

	m_isHitAttack = false;
	m_hp = 100;

	m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
};

//-------------------------------------
//�G����łǂ��Ɉʒu���Ă��邩�v�Z����

void Character::SetOnRadarPos()
{
	const float radarWidth = oka::Screen::GetInstance()->GetWidth() / 3.0f;
	const float radarHeight = oka::Screen::GetInstance()->GetHeight() / 3.0f;

	const float fealdWidth = oka::FealdManager::GetInstance()->m_feald->m_width;
	const float fealdHeight = oka::FealdManager::GetInstance()->m_feald->m_height;

	m_onRadarPos.x = m_transform.m_position.x * (radarWidth / fealdWidth);
	m_onRadarPos.y = -m_transform.m_position.z * (radarHeight / fealdHeight);
}

//-------------------------------------
//�n�`�������ɂ��邩�O�ɂ��邩�̔���

bool Character::IsGroundOut()const
{
	//x
	const float width = oka::FealdManager::GetInstance()->m_feald->m_width;
	const float x = m_transform.m_position.x;

	if (x < 0 || width < x)
	{
		return  true;
	}

	//z
	const float height = oka::FealdManager::GetInstance()->m_feald->m_height;
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

	const int width = oka::FealdManager::GetInstance()->m_feald->m_width;

	const float height = oka::FealdManager::GetInstance()->m_feald->m_vertex[z * width + x].y;

//debug
//printf("h:%f\n", height);

	if ( y <= height)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//HP�̒l���Q�Ƃ�0�ȉ��ɂȂ��Ă����true
//�����łȂ����false��Ԃ�

bool Character::IsDead()const
{
	if (m_hp <= 0)
	{	
		return true;
	}

	return false;
	
}
