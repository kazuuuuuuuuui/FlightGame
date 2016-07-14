#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"../MyLibrary/Input/Controller.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/JoysticManager.h"
#include"..//MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/EffectManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../glm/glm.hpp"
#include"../glm/gtc/matrix_transform.hpp"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"
#include"../glm/gtx/transform.hpp"
#include"../glm/gtx/intersect.hpp"
#include"../Bullet/HomingBullet.h"
#include"../glm/gtc/quaternion.hpp"
#include"../glm/gtx/quaternion.hpp"

#include"../glut.h"


//-------------------------------------
//�R���X�g���N�^

Player::Player():
	m_isRockOn(false),
	m_target(nullptr)
{
	m_controller = oka::JoysticManager::GetInstance()->GetController(0);

	m_transform.m_position = glm::vec3(130.0f, 30.0f, 180.0f);
}

//-------------------------------------
//�f�X�g���N�^

Player::~Player()
{

}

//-------------------------------------
//���@�̐���

PlayerSP Player::Create()
{
	PlayerSP player(new Player());

	return player;
}


//-------------------------------------
//�X�V

void Player::Update()
{
	//���W�X�V
	m_speed = m_transform.m_myToVec*0.2f + m_accel;
	m_transform.m_position += m_speed;

	SetOnRadarPos();

	//����
	m_accel *= 0.98f;
	m_speed *= 0.98f;

	//�{�f�B
	m_body->m_transform = m_transform;

	//��
	if (0 == m_flame % 3)
	{
		const glm::vec3 basePos = m_transform.m_position - m_transform.m_myUpVec*0.5f;
		SmokeSP smoke = Smoke::Create(basePos, 1, glm::vec3(195.0f / 255.0f, 195.0f / 255.0f, 195.0f / 255.0f));
		oka::GameManager::GetInstance()->Add("Smoke", smoke);
	}

	if (m_isRockOn)
	{
		oka::SoundManager::GetInstance()->Play("RockOn");
	}
	else
	{
		oka::SoundManager::GetInstance()->Stop("RockOn");
	}


	/*����������*/
	if (m_transform.m_position.x <= -200.0f)
	{
		m_transform.m_position.x = -200.0f;
	}
	if (m_transform.m_position.x >= 400.0f)
	{
		m_transform.m_position.x = 400.0f;
	}
	if (m_transform.m_position.z >= 180.0f)
	{
		m_transform.m_position.z = 180.0f;
	}
	if (m_transform.m_position.z <= -450.0f)
	{
		m_transform.m_position.z = -450.0f;
	}
	if (m_transform.m_position.y >= 250.0f)
	{
		m_transform.m_position.y = 250.0f;
	}

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

	if (0 == m_flame % 60)
	{
		m_isHitAttack = false;
	}

	std::tie(m_isRockOn, m_target) = SetTarget();

	if (IsGroundOut())
	{
		if(IsIntersectSea())
		{
			m_isActive = false;
			m_body->m_isActive = false;
		}
	}
	else
	{
		if (IsIntersectGround())
		{
			m_isActive = false;
			m_body->m_isActive = false;
		}
	}

	//���S����
	if (false == m_isActive)
	{
		//������
		oka::SoundManager::GetInstance()->Play("Explode");

		//�����G�t�F�N�g
		SmokeSP smoke = Smoke::Create(m_transform.m_position, 5, glm::vec3(0.0f, 0.0f, 0.0f));
		oka::GameManager::GetInstance()->Add("Smoke", smoke);

		FireSP fire = Fire::Create(m_transform.m_position, 20, glm::vec3(1.0f, 0.5f, 0.25f));
		oka::GameManager::GetInstance()->Add("Fire", fire);
	}
}

//-------------------------------------
//�L�[�{�[�h�ł̑���

void Player::Control()
{
	Accel();
	Shot();
	HomingShot();

	glm::tquat<float> quat;
	const float rotateSpeed = glm::radians(1.0f);

	/*
	//Roll
	if (_sThumbLX > 0.5f)
	{
		quat = oka::MyMath::Rotate(rotateSpeed, glm::vec3(0, 0, -1));

		m_transform.m_rotate *= quat;

	}
	else if (_sThumbLX < -0.5f)
	{
		quat = oka::MyMath::Rotate(-rotateSpeed, glm::vec3(0, 0, -1));

		m_transform.m_rotate *= quat;
	}

	//Pitch
	if (_sThumbLY > 0.5f)
	{
		quat = oka::MyMath::Rotate(-rotateSpeed / 2.0f, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
	else if (_sThumbLY < -0.5f)
	{
		quat = oka::MyMath::Rotate(rotateSpeed / 2.0f, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
	*/

}

//-------------------------------------
//�Q�[���p�b�h�ł̑���

void Player::Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY)
{
	Accel(_pressedKey);
	Shot(_downKeys);
	HomingShot(_downKeys);

	glm::tquat<float> quat;
	const float rotateSpeed = glm::radians(1.5f);

	//debug
	/*if (_pressedKey & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		quat = oka::MyMath::Rotate(-rotateSpeed, glm::vec3(0, 1, 0));

		m_transform.m_rotate *= quat;

	}
	else if (_pressedKey & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		quat = oka::MyMath::Rotate(rotateSpeed, glm::vec3(0, 1, 0));

		m_transform.m_rotate *= quat;
	}
	*/

	//Roll
	if (_sThumbLX > 0.5f)
	{
		quat = oka::MyMath::Rotate(rotateSpeed, glm::vec3(0, 0, -1));

		m_transform.m_rotate *= quat;

	}
	else if (_sThumbLX < -0.5f)
	{
		quat = oka::MyMath::Rotate(-rotateSpeed, glm::vec3(0, 0, -1));

		m_transform.m_rotate *= quat;
	}

	//Pitch
	if (_sThumbLY > 0.5f)
	{
		quat = oka::MyMath::Rotate(-rotateSpeed / 2.0f, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
	else if (_sThumbLY < -0.5f)
	{
		quat = oka::MyMath::Rotate(rotateSpeed / 2.0f, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
}

//-------------------------------------
//�L�[�{�[�h
//�L�[�{�[�h '�X�y�[�X' �O�i����
//�X�y�[�X�L�[ �őO�i

void Player::Accel()
{
	if (oka::Keyboard::GetStates(' '))
	{
		const float value = 0.03f;//�����x��Ԓl
		m_accel += m_transform.m_myToVec*value;
	}
}

//-------------------------------------
//�Q�[���p�b�h
//�O�i����
//A�{�^�������������Ă���ԑO�i

void Player::Accel(unsigned short _pressedKey)
{
	if (_pressedKey & XINPUT_GAMEPAD_A)
	{
		const float value = 0.008f;//�����x��Ԓl
		m_accel += m_transform.m_myToVec*value;
	}
}

//-------------------------------------
//�L�[�{�[�h
//�L�[�{�[�h 'b' �Œe�ɂ��U��
//�e�̍��W�����g�̍��W�ɃZ�b�g��
//�e�̃X�s�[�h��ݒ肷��

void Player::Shot()
{
	if (oka::Keyboard::GetStates('b'))
	{
		oka::SoundManager::GetInstance()->ChangeVolume("Shot", 1.0f);
		oka::SoundManager::GetInstance()->Play("Shot");

		glm::vec3 pos;
		const float distance = 5.0f;//���@�ƒe���˓_�̊Ԋu
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 3.0f;//�e�̃X�s�[�h�⊮�l
		speed = m_transform.m_myToVec * value;

		glm::tquat<float> mat = m_transform.m_rotate;

		BulletSP bullet = Bullet::Create(pos, mat, speed);
		oka::BulletManager::GetInstance()->SetBullet(bullet);
		oka::GameManager::GetInstance()->Add("Bullet", bullet);
	}
}

//-------------------------------------
//�Q�[���p�b�h
//x�{�^���Œe�ɂ��U��

void Player::Shot(unsigned short _downKeys)
{
	if (_downKeys & XINPUT_GAMEPAD_X)
	{
		oka::SoundManager::GetInstance()->ChangeVolume("Shot", 1.0f);
		oka::SoundManager::GetInstance()->Play("Shot");

		glm::vec3 pos;
		const float distance = 3.0f;//���@�ƒe���˓_�̊Ԋu
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 3.0f;//�e�̃X�s�[�h�⊮�l
		speed = m_transform.m_myToVec * value;

		glm::tquat<float> mat = m_transform.m_rotate;

		BulletSP bullet = Bullet::Create(pos, mat, speed);
		oka::BulletManager::GetInstance()->SetBullet(bullet);
		oka::GameManager::GetInstance()->Add("Bullet", bullet);
	}
}

//-------------------------------------
//�L�[�{�[�h
//�L�[�{�[�h 'h' �Ńz�[�~���O�e�ɂ��U��
//���b�N�I����Ԃ̂Ƃ��̂ݎˌ��\

void Player::HomingShot()
{
	if (m_isRockOn && (oka::Keyboard::GetStates('h')))
	{
		oka::SoundManager::GetInstance()->Play("HomingBullet");

		//���@�ƒe���˓_�̊Ԋu
		const float downDis = 5.0f;
		const float toDis = 25.0f;

		const glm::vec3 pos = m_transform.m_position + m_transform.m_myToVec*toDis - m_transform.m_myUpVec*downDis;

		glm::vec3 speed;
		speed = m_transform.m_myToVec;

		const glm::tquat<float>quat = m_transform.m_rotate;

		HomingBulletSP homingBullet = HomingBullet::Create(m_target, pos, quat, speed);
		oka::BulletManager::GetInstance()->SetBullet(homingBullet);
		oka::GameManager::GetInstance()->Add("HomingBullet", homingBullet);
	}
}

//-------------------------------------
//�Q�[���p�b�h
//Y�{�^���Ńz�[�~���O�e�ɂ��U��
//���b�N�I����Ԃ̂Ƃ��̂ݎˌ��\

void Player::HomingShot(unsigned short _downKeys)
{
	if (m_isRockOn && (_downKeys & XINPUT_GAMEPAD_Y))
	{
		oka::SoundManager::GetInstance()->Play("HomingBullet");

		//���@�ƒe���˓_�̊Ԋu
		const float downDis = 5.0f;
		const float toDis = 25.0f;
		
		const glm::vec3 pos = m_transform.m_position + m_transform.m_myToVec*toDis - m_transform.m_myUpVec*downDis;

		glm::vec3 speed;
		speed = m_transform.m_myToVec;
	
		const glm::tquat<float>quat = m_transform.m_rotate;

		HomingBulletSP homingBullet = HomingBullet::Create(m_target, pos, quat, speed);
		oka::BulletManager::GetInstance()->SetBullet(homingBullet);
		oka::GameManager::GetInstance()->Add("HomingBullet", homingBullet);
	}
}

//-------------------------------------
//�I�̕`��ʒu����

std::tuple<bool, glm::vec3*> Player::SetTarget()
{
	const glm::vec3 pos = m_transform.m_position;
	const glm::vec3 dir = m_transform.m_myToVec;
	const float rad = 100.0f;
	float distance;

	auto itr = oka::CharacterManager::GetInstance()->GetCharacters()->begin();
	auto end = oka::CharacterManager::GetInstance()->GetCharacters()->end();

	while (itr != end)
	{
		static const float dis = 200.0f;
		//const glm::vec3 pos = ;
		if (IsNear((*itr)->m_transform.m_position,dis))
		{
			if (glm::intersectRaySphere(pos, dir, (*itr)->m_transform.m_position, rad, distance))
			{
				return std::make_tuple(true, &((*itr)->m_transform.m_position));
			}
		}

		//debug
		else
		{
			printf("aaa\n");
		}

		itr++;
	}

	return std::make_tuple(false, nullptr);
}

//-------------------------------------
//�e�̍s����߂�ׂ̓I�̕`��

void Player::DrawTarget()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//�I�̏c��
		static const float width = 3.0f;
		static const float height = 3.0f;
		
		//�`��ꏊ�ƃe�N�X�`���̐ݒ�
		unsigned int tex;
	
		glPushMatrix();
		{
			if (m_isRockOn)
			{	
				tex = oka::ImageManager::GetInstance()->GetHandle("RockOn");
				glTranslatef((*m_target).x, (*m_target).y, (*m_target).z);
			}
			else
			{
				tex = oka::ImageManager::GetInstance()->GetHandle("Target");

				const float value = 30.0f;//�L�����N�^�[�Ƃ̊Ԋu�⊮�l
				const glm::vec3 pos = m_transform.m_position;
				const glm::vec3 toVec = m_transform.m_myToVec*value;
				const glm::vec3 v = pos + toVec;

				glTranslatef(v.x, v.y, v.z);
			}

			glMultMatrixf((GLfloat*)&BillboardMatrix);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex);
			
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0.0f, 0.0f); glVertex2f(-width / 2, -height / 2);
				glTexCoord2f(1.0f, 0.0f); glVertex2f(width / 2, -height / 2);
				glTexCoord2f(1.0f, 1.0f); glVertex2f(width / 2, height / 2);
				glTexCoord2f(0.0f, 1.0f); glVertex2f(-width / 2, height / 2);
			}
			glEnd();
		}
		glPopMatrix();
	}
	glPopAttrib();

}

//-------------------------------------
//�G����ł̎����̈ʒu��`�悷��

void Player::DrawRadarPos()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glColor3f(0, 0, 1);
		glPointSize(15);

		glBegin(GL_POINTS);
		{
			glVertex2f(m_onRadarPos.x, m_onRadarPos.y);
		}
		glEnd();
	}
	glPopAttrib();
}