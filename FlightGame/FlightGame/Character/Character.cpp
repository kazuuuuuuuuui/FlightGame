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
#include"../glm/gtx/transform.hpp"
#include"../glut.h"


//-------------------------------------
//�R���X�g���N�^

Character::Character()
{
	printf("�L�����N�^�[����\n");

	m_transform.m_scale = glm::vec3(0.3f, 0.6f, 0.3f);


	//�̕���
	oka::Model *body = oka::ModelManager::GetInstance()->m_models["Body"];
	unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("FlyTex"));
	m_body = new oka::Mesh(body, tex);
	oka::GameManager::GetInstance()->AddGameObject("Body", m_body);

	//�v���y������
	/*oka::Model *propeller = oka::ModelManager::GetInstance()->m_models["Propeller"];
	m_propeller = new oka::Mesh(propeller, tex);
	m_propeller->m_transform.m_scale = glm::vec3(0.5f, 1.0f, 0.5f);
	oka::GameManager::GetInstance()->AddGameObject("Propeller", m_propeller);*/

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
	//glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 0.0f, -10.0f));

	
   //�v���y��
	/*m_propeller->m_transform.m_translateMatrix = m_transform.m_translateMatrix;
	m_propeller->m_transform.m_rotateMatrix = m_transform.m_rotateMatrix;

	m_propeller->m_transform.m_matrix *= offSet;*/
	//

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


	//���S����
	if (m_isActive)
	{
		if (CheckIsDead())
		{
			m_isActive = false;
			m_body->m_isActive = false;
			
			//������
			oka::SoundManager::GetInstance()->Play("Explode");

			//�����G�t�F�N�g
			const unsigned int num = 15;
			oka::GameManager::GetInstance()->AddGameObject("Smoke", Smoke::Create(m_transform.m_position, num));
			oka::GameManager::GetInstance()->AddGameObject("Fire", Fire::Create(m_transform.m_position));
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
