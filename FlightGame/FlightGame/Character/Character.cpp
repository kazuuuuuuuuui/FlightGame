#define _USE_MATH_DEFINES
#include<math.h>
#include"Character.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/FealdManager.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"Player.h"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"
#include"../glm/gtx/transform.hpp"
#include"../glut.h"


//-------------------------------------
//�R���X�g���N�^

Character::Character()
{
	m_transform.m_scale = glm::vec3(0.3f, 0.6f, 0.3f);

	//�̕���
	oka::ModelSP body = oka::ModelManager::GetInstance()->m_models["Body"];
	unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("FlyTex"));
	m_body = oka::Mesh::Create(body, tex);
	oka::GameManager::GetInstance()->Add("Body", m_body);

	//�v���y������
	oka::ModelSP propeller = oka::ModelManager::GetInstance()->m_models["Propeller"];
	m_propeller = oka::Mesh::Create(propeller, tex);
	oka::GameManager::GetInstance()->Add("Propeller", m_propeller);

	m_controller = new oka::Contoroller();
	oka::JoysticManager::GetInstance()->AddController(m_controller);

	m_isHitAttack = false;
	m_hp = 100;

	m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
};

void Character::Update()
{
	//���W�X�V
	m_speed += m_accel;
	m_transform.m_position += m_speed;

	//����
	m_speed *= 0.965f;

	//�{�f�B
	m_body->m_transform = m_transform;

	//�I�t�Z�b�g�v�Z
	glm::mat4 offSet;
	
	const glm::mat4 translate = glm::translate(glm::vec3(0.0f, 0.3f, -5.2f));
	
	//static float angle = 0.0f;
	//angle += oka::MyMath::ToRadian(2.0f);
	//const glm::vec3 axis = glm::vec3(0, 1, 0);
	//const glm::mat4 rotate = glm::rotate(angle, axis);

	const glm::mat4 scale = glm::scale(glm::vec3(2, 2, 2));

	offSet = translate*scale;

   //�v���y��
	m_propeller->m_transform = m_transform;
	m_propeller->m_transform.m_matrix = m_transform.m_matrix * offSet;
	

	if (m_controller->IsConected())
	{
		unsigned short pressedKey = m_controller->m_state.Gamepad.wButtons;
		unsigned int downKeys = m_controller->m_downkey;
		float sThumbLX = m_controller->m_sThumbLX;
		float sThumbLY = m_controller->m_sThumbLY;

		Control(pressedKey, downKeys, sThumbLX, sThumbLY);
	}
	else
	{
		Control();
	}
	
	if (m_isHitAttack)
	{
		//��������
		m_hp -= 100;
	}

	m_isHitAttack = false;


//debug
glm::vec3 pos = m_transform.m_position;
//printf("x:%f,y:%f,z:%f\n", pos.x, pos.y, pos.z);



	//�t�B�[���h�Ƃ̔���
	if (IsGroundOut())
	{
//debug
//printf("�o�Ă�您������������������\n");
	}
	else
	{
		if (IsIntersectGround())
		{
//debug
//printf("�n�ʂɓ������Ă�您��������������\n");
			m_hp = 0;
		}
	}

	//���S����
	if (m_isActive)
	{
		if (IsDead())
		{
			m_isActive = false;
			m_body->m_isActive = false;
			m_propeller->m_isActive = false;
			
			//������
			oka::SoundManager::GetInstance()->Play("Explode");

			//�����G�t�F�N�g
			const unsigned int num = 15;
			oka::GameManager::GetInstance()->Add("Smoke", Smoke::Create(m_transform.m_position, num));
			oka::GameManager::GetInstance()->Add("Fire", Fire::Create(m_transform.m_position));
		}
	}
}

//-------------------------------------
//�Q�[���p�b�h�ł̑���

void Character::Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY)
{
	Accel(_pressedKey);
	Shot(_downKeys);

	const float value = oka::MyMath::ToRadian(1.0f);

	//Roll
	if (_pressedKey & XINPUT_GAMEPAD_B)
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(0, 0, -1));
	}
	else if (_pressedKey & XINPUT_GAMEPAD_X)
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(0, 0, -1));
	}

	//Yaw
	if (_sThumbLX > 0.5f)
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(0, 1, 0));
	}
	else if (_sThumbLX < -0.5f)
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(0, 1, 0));
	}

	//Pitch
	if (_sThumbLY > 0.5f)
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(1, 0, 0));
	}
	else if (_sThumbLY < -0.5f)
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(1, 0, 0));
	}
}

//-------------------------------------
//�O�i����
//�Q�[���p�b�h A �őO�i

void Character::Accel(unsigned short _pressedKey)
{
	if (_pressedKey & XINPUT_GAMEPAD_A)
	{
		const float value = 0.02f;

		glm::vec3 accel;
		accel = m_transform.m_myToVec*value;

		m_accel = accel;
	}
	else
	{
		m_accel = glm::vec3(0, 0, 0);
	}

}

//-------------------------------------
//�e�ɂ��U��

void Character::Shot(unsigned short _downKeys)
{
	if (_downKeys & XINPUT_GAMEPAD_Y)
	{
		oka::SoundManager::GetInstance()->Play("Shot");

		glm::vec3 pos;
		const float distance = 2.0f;//���@�ƒe���˓_�̊Ԋu
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 4.0f;//�e�̃X�s�[�h�⊮�l
		speed = m_transform.m_myToVec * value;

		glm::mat4 mat = m_transform.m_rotate;

		BulletSP bullet = Bullet::Create(pos, mat, speed);
		oka::BulletManager::GetInstance()->Add(bullet);
		oka::GameManager::GetInstance()->Add("Bullet", bullet);
	}
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
