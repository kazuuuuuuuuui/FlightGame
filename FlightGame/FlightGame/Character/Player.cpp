#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"../MyLibrary/Input/Controller.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"..//MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Manager/EffectManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Camera/Camera.h"
#include"../glm/glm.hpp"
#include"../glm/gtc/matrix_transform.hpp"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"
#include"../glm/gtx/transform.hpp"
#include"../glm/gtx/intersect.hpp"


#include"../Bullet/HomingBullet.h"


#include"../glut.h"


//-------------------------------------
//�R���X�g���N�^

Player::Player(glm::vec3 _pos):
	m_targetPos(glm::vec3(0.0f, 0.0f, 0.0f))
{
	m_controller = new oka::Contoroller();
	oka::JoysticManager::GetInstance()->AddController(m_controller);

	m_transform.m_position = _pos;
}

//-------------------------------------
//�f�X�g���N�^

Player::~Player()
{

}

//-------------------------------------
//���@�̐���

PlayerSP Player::Create(glm::vec3 _pos)
{
	PlayerSP player(new Player(_pos));

	return player;
}

//-------------------------------------
//�X�V

void Player::Update()
{
//debug
//printf("x:%fy:%fz:%f\n", m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z);

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
		//m_hp -= 100;
	}

	if (IsGroundOut())
	{
		if(IsIntersectSea())
		{
//debug
printf("�C�̒���������������\n");
		}
	}
	else
	{
		SetOnRadarPos();

		if (IsIntersectGround())
		{
//debug
printf("�������Ă邤��������\n");
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
//�L�[�{�[�h�ł̑���

void Player::Control()
{
	Accel();
	Shot();

	const float value = oka::MyMath::ToRadian(1.0f);

	//Roll
	if (oka::Keyboard::GetStates('m'))
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(0, 0, -1));
	}
	else if (oka::Keyboard::GetStates('n'))
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(0, 0, -1));
	}

	//Yaw
	if (oka::Keyboard::GetStates('d'))
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(0, 1, 0));
	}
	else if (oka::Keyboard::GetStates('a'))
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(0, 1, 0));
	}

	//Pitch
	if (oka::Keyboard::GetStates('s'))
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(1, 0, 0));
	}
	else if (oka::Keyboard::GetStates('w'))
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(1, 0, 0));
	}

}

//-------------------------------------
//�Q�[���p�b�h�ł̑���

void Player::Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY)
{
	Accel(_pressedKey);
	Shot(_downKeys);
	HomingShot(_downKeys);

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
		//m_transform.m_rotate *= oka::MyMath::Rotate(value / 10.0f, glm::vec3(0, 0, -1));
		m_transform.m_rotate *= oka::MyMath::Rotate(-value, glm::vec3(0, 1, 0));
	}
	else if (_sThumbLX < -0.5f)
	{
		//m_transform.m_rotate *= oka::MyMath::Rotate(-value / 10.0f, glm::vec3(0, 0, -1));
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
//�L�[�{�[�h �X�y�[�X�L�[ �őO�i

void Player::Accel()
{
	if (oka::Keyboard::GetStates(' '))
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
//�O�i����
//�Q�[���p�b�h A �őO�i

void Player::Accel(unsigned short _pressedKey)
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
//�e�̍��W�����g�̍��W�ɃZ�b�g��
//�e�̃X�s�[�h��ݒ肷��

void Player::Shot()
{
	if (oka::Keyboard::GetStates('b'))
	{
		oka::SoundManager::GetInstance()->ChangeVolume("Shot", 1.0f);
		oka::SoundManager::GetInstance()->Play("Shot");
		
		glm::vec3 pos;
		const float distance = 2.0f;//���@�ƒe���˓_�̊Ԋu
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 4.0f;//�e�̃X�s�[�h�⊮�l
		speed = m_transform.m_myToVec * value;

		glm::mat4 mat = m_transform.m_rotate;
	
		BulletSP bullet = Bullet::Create(pos, mat, speed);
		oka::BulletManager::GetInstance()->AddBullet(bullet);
		oka::GameManager::GetInstance()->Add("Bullet", bullet);
	}
}

//-------------------------------------
//�e�ɂ��U��

void Player::Shot(unsigned short _downKeys)
{
	if (_downKeys & XINPUT_GAMEPAD_Y)
	{
		oka::SoundManager::GetInstance()->ChangeVolume("Shot", 1.0f);
		oka::SoundManager::GetInstance()->Play("Shot");

		glm::vec3 pos;
		const float distance = 2.0f;//���@�ƒe���˓_�̊Ԋu
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 4.0f;//�e�̃X�s�[�h�⊮�l
		speed = m_transform.m_myToVec * value;

		glm::mat4 mat = m_transform.m_rotate;

		BulletSP bullet = Bullet::Create(pos, mat, speed);
		oka::BulletManager::GetInstance()->AddBullet(bullet);
		oka::GameManager::GetInstance()->Add("Bullet", bullet);
	}
}

//-------------------------------------
//�z�[�~���O�e�ɂ��U��

void Player::HomingShot(unsigned short _downKeys)
{
	//if (_downKeys & XINPUT_GAMEPAD_B)
	//{
	//	const float distance = 2.0f;//���@�ƒe���˓_�̊Ԋu
	//	const glm::vec3 pos = m_transform.m_position + m_transform.m_myToVec*distance;

	//	glm::vec3 speed;
	//	const float value = 4.0f;//�e�̃X�s�[�h�⊮�l
	//	speed = m_transform.m_myToVec * value;
	//
	//	const glm::mat4 mat = m_transform.m_rotate;

	//	HomingBulletSP homingBullet = HomingBullet::Create(m_targetPos, pos, mat, speed);
	//	oka::BulletManager::GetInstance()->AddBullet(homingBullet);
	//	oka::GameManager::GetInstance()->Add("HomingBullet", homingBullet);
	//}
}

//-------------------------------------
//�I�̕`��ʒu����

std::tuple<bool, glm::vec3> Player::SetTarget()
{
	const glm::vec3 pos = m_transform.m_position;
	const glm::vec3 dir = m_transform.m_myToVec;
	const float rad = 50.0f;
	float distance;

	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();//�G����
	itr++;
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while (itr != end)
	{
		const glm::vec3 aimPos = (*itr)->m_transform.m_position;

		if (IsNear(aimPos))
		{
			if (glm::intersectRaySphere(pos, dir, aimPos, rad, distance))
			{
				return std::make_tuple(true, aimPos);
			}
		}
		itr++;
	}


	const float value = 30.0f;//�L�����N�^�[�Ƃ̊Ԋu�⊮�l		
	const glm::vec3 toVec = m_transform.m_myToVec*value;
	const glm::vec3 v = pos + toVec;

	return std::make_tuple(false, v);
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
		const float width = 3.0f;
		const float height = 3.0f;

		//�`��ꏊ
		unsigned int tex;

		bool flag;
		std::tie(flag, m_targetPos) = SetTarget();

		if (flag)
		{
			tex = oka::ImageManager::GetInstance()->GetHandle("RockOn");
		}
		else
		{
			tex = oka::ImageManager::GetInstance()->GetHandle("Target");
		}
		//debug
//printf("x:%fy:%fz:%f\n", m_targetPos.x, m_targetPos.y, m_targetPos.z);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glPushMatrix();
		{
			glTranslatef(m_targetPos.x, m_targetPos.y, m_targetPos.z);
			glMultMatrixf((GLfloat*)&BillboardMatrix);
			
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
//������͈͓��Ɉ����̍��W�����݂��邩�𔻕ʂ���

bool Player::IsNear(glm::vec3 _pos)const
{
	const glm::vec3 pos = _pos - m_transform.m_position;
	const float distance = glm::length(pos);

	const float value = 80.0f;

	if (distance < value)
	{
		return true;
	}


	return false;
}