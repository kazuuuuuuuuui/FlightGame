#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../Effect/Fire.h"
#include"../Effect/Smoke.h"
#include"../glm/gtx/transform.hpp"
#include"../glm/gtx/intersect.hpp"
#include"../glut.h"

//-------------------------------------
//�R���X�g���N�^

Enemy::Enemy(glm::vec3 _pos)
{
	const float x_max = 256.0f;
	m_aimPos.x = ((float)rand() / RAND_MAX)*x_max;

	const float bottom = 20.0f;
	m_aimPos.y = bottom + ((float)rand() / RAND_MAX)*10.0f;

	const float z_max = -256.0f;
	m_aimPos.z = ((float)rand() / RAND_MAX)*z_max;


	m_transform.m_position = _pos;
}


//-------------------------------------
//�G�̐���

EnemySP Enemy::Create(glm::vec3 _pos)
{
	EnemySP enemy(new Enemy(_pos));

	return enemy;
}

//-------------------------------------
//�X�V

void Enemy::Update()
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


	Control();


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
		SetOnRadarPos();

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
			//oka::GameManager::GetInstance()->Add("Smoke", Smoke::Create(m_transform.m_position));
			//oka::GameManager::GetInstance()->Add("Fire", Fire::Create(m_transform.m_position));
		}
	}
}

//-------------------------------------
//�e�ɂ��U��

void Enemy::Shot()
{
	const glm::vec3 v = m_transform.m_position - oka::CharacterManager::GetInstance()->m_player->m_transform.m_position;
	float volume = glm::length(v);
	volume = 20.0f / volume;

//debug
//printf("%f\n", volume);

	oka::SoundManager::GetInstance()->ChangeVolume("Shot", volume);
	oka::SoundManager::GetInstance()->Play("Shot");

	glm::vec3 pos;
	const float distance = 2.0f;//���@�ƒe���˓_�̊Ԋu
	pos = m_transform.m_position + m_transform.m_myToVec*distance;

	glm::vec3 speed;
	const float value = 5.0f;//�e�̃X�s�[�h�⊮�l
	speed = m_transform.m_myToVec * value;

	glm::mat4 mat = m_transform.m_rotate;

	BulletSP bullet = Bullet::Create(pos, mat, speed);
	oka::BulletManager::GetInstance()->AddBullet(bullet);
	oka::GameManager::GetInstance()->Add("Bullet", bullet);
}

//-------------------------------------
//�G��AI

void Enemy::Control()
{
	const glm::vec3 pos = m_transform.m_position;
	const glm::vec3 dir = m_transform.m_myToVec;
	const glm::vec3 aimPos = oka::CharacterManager::GetInstance()->m_player->m_transform.m_position;
	const float rad = 50.0f;
	float distance;

	if (glm::intersectRaySphere(pos, dir, aimPos, rad, distance))
	{
		//20F��1��e����
		if (0 == (m_flame % 10))
		{
			Shot();
		}
	}
	
	/*glm::vec3 v = m_aimPos - m_transform.m_position;

	if (glm::length(v) <= 5.0f)
	{
		ResetAimPos();
	}

	v = glm::normalize(v);
	v *= 0.01f;*/
	//m_accel = v;
//printf("x:%f,y:%f,z:%f\n", m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z);

}

//-------------------------------------
//�ڕW�_�̍Đݒ�

void Enemy::ResetAimPos()
{
	const float x_max = 256.0f;
	m_aimPos.x = ((float)rand() / RAND_MAX)*x_max;

	const float bottom = 20.0f;
	m_aimPos.y = bottom + ((float)rand() / RAND_MAX)*10.0f;

	const float z_max = -256.0f;
	m_aimPos.z = ((float)rand() / RAND_MAX)*z_max;
}