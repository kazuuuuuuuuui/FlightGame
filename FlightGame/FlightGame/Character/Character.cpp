#define _USE_MATH_DEFINES
#include<math.h>
#include"Character.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"Player.h"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"

#include"../glut.h"

//-------------------------------------
//�R���X�g���N�^

Character::Character()
{
	printf("�L�����N�^�[����\n");

	//���f���f�[�^�傫������
	m_transform.SetScale(glm::vec3(0.3f, 0.6f, 0.3f));

	//�̕���
	oka::Model *body = oka::ModelManager::GetInstance()->m_models["Body"];
	unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("FlyTex"));
	m_body = new oka::Mesh(body, tex);
	oka::GameManager::GetInstance()->AddGameObject("Body", m_body);

	//�v���y������
	/*oka::Model *propeller = oka::ModelManager::GetInstance()->m_models["Propeller"];
	m_propeller = new oka::Mesh(propeller, tex);
	oka::GameManager::GetInstance()->AddGameObject("Propeller", m_propeller);*/



	m_controller = new oka::Contoroller();
	oka::JoysticManager::GetInstance()->AddController(m_controller);

	m_isHitAttack = false;
	m_hp = 100;

	//��ŕύX	
	m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
};

//-------------------------------------
//���g�̕`��
//���f���}�l�[�W���[���烂�f���f�[�^���Q�Ƃ���

void Character::Draw()
{
	
}

void Character::Update()
{
	//�{�f�B
	m_body->m_transform = m_transform;

	//�v���y��
	/*glm::mat4 translate;
	translate = glm::translate(translate, glm::vec3(0.0f, 0.1f, -5.2f));*/

	//glm::mat4 rotate;
	//static float angle = 0.0f;
	//angle += 0.2f;
	//rotate = oka::MyMath::Rotate(angle, glm::vec3(0.0f, 0.0f, -1.0f));
	//m_propeller->m_transform.m_matrix = m_transform.m_matrix*translate;//*rotate;




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
		m_hp -= 100;
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
			m_body->m_isActive = false;
			m_isActive = false;
			

			//������
			oka::SoundManager::GetInstance()->Play("Explode");

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
