#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"../MyLibrary/Input/Controller.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
//#include"../Effect/Smoke.h"
#include"../MyLibrary/Manager/EffectManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Camera/Camera.h"

#include"../glm/glm.hpp"
#include"../glm/gtc/matrix_transform.hpp"

#include"../glut.h"

//-------------------------------------
//�L�[�{�[�h�ł̑���

void Player::Control()
{
	//Accel();
	//Yaw();
	//Roll();

	//Shot();

	//const float value = 0.4f * ((float)M_PI / 180.0f);


	////�㏸
	//if (oka::Keyboard::GetStates('s'))
	//{
	//	//m_transform.SetRotationX(m_transform.GetRotation().x + value);
	//}

	////���~
	//else if (oka::Keyboard::GetStates('w'))
	//{
	//	//m_transform.SetRotationX(m_transform.GetRotation().x - value);
	//}

	////���̎p���ɖ߂�
	//else
	//{
	//	//.SetRotationX(m_transform.GetRotation().m_x - (m_transform.GetRotation().m_x)*0.1f);
	//}
}

//-------------------------------------
//�Q�[���p�b�h�ł̑���

void Player::Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY)
{
	//m_speed = m_transform.m_myToVec*0.2f;
	m_speed += m_accel;

	Accel(_pressedKey);

	const float value = oka::MyMath::ToRadian(1.0f);

	//Roll
	if (_pressedKey & XINPUT_GAMEPAD_B)
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(value, glm::vec3(0, 0, -1));
	}
	else if(_pressedKey & XINPUT_GAMEPAD_X)
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

	Shot(_downKeys);

	//��ŕύX
	//DrawTarget();
}

//-------------------------------------
//�O�i����
//�L�[�{�[�h �X�y�[�X�L�[ �őO�i

/*

�i�܂Ȃ�

*/

void Player::Accel()
{
	//if (oka::Keyboard::GetStates(' '))
	//{
	//	const float value = -0.05f;//�⊮�W��
	//	glm::vec3 accel;
	//	accel.x = value*sin(m_transform.GetRotation().y);
	//	accel.y = (-1)*value*sin(m_transform.GetRotation().x);
	//	accel.z = value*cos(m_transform.GetRotation().y);
	//}
	//else
	//{
	//	m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
	//}
}

//-------------------------------------
//�O�i����
//�Q�[���p�b�h A �őO�i

void Player::Accel(unsigned short _pressedKey)
{
	if (_pressedKey & XINPUT_GAMEPAD_A)
	{
		const float value = 0.01f;
		
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
//�L�[�{�[�h�ɂ�����




//-------------------------------------
//�e�ɂ��U��
//�e�̍��W�����g�̍��W�ɃZ�b�g��
//�e�̃X�s�[�h��ݒ肷��

void Player::Shot()
{
	/*if (oka::Keyboard::GetStates('b'))
	{
		glm::vec3 pos;
		const float distance = 1.5f;
		pos.x = m_transform.GetPosition().x - sin(m_transform.GetRotation().y)*distance;
		pos.y = m_transform.GetPosition().y;
		pos.z = m_transform.GetPosition().z - cos(m_transform.GetRotation().y)*distance;

		glm::vec3 rotate = m_transform.GetRotation();

		glm::vec3 speed;
		float value = 0.1f;
	
		speed.x = -sin(m_transform.GetRotation().y) * value*(180.0f / M_PI);
		speed.y = sin(m_transform.GetRotation().x)* value*(180.0f / M_PI);
		speed.z = -cos(m_transform.GetRotation().y) * value*(180.0f / M_PI);

		m_bullets.push_back(new Bullet(pos, rotate, speed));
	}*/
}

//-------------------------------------
//�e�ɂ��U��

void Player::Shot(unsigned short _downKeys)
{
	if (_downKeys & XINPUT_GAMEPAD_Y)
	{
		glm::vec3 pos;
		const float distance = 2.0f;//���@�ƒe���˓_�̊Ԋu
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 4.0f;//�e�̃X�s�[�h�⊮�l
		speed = m_transform.m_myToVec * value;

		glm::mat4 mat = m_transform.m_rotate;
	
		oka::SoundManager::GetInstance()->Play("Shot");
		Bullet *bullet = new Bullet(pos, speed, mat);

		oka::BulletManager::GetInstance()->AddBullet(bullet);
		oka::GameManager::GetInstance()->AddGameObject("Bullet", bullet);
	}
}


//-------------------------------------
//�e�̍s����߂�ׂ̓I�̕`��

void Player::DrawTarget()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		const unsigned int texture = oka::ImageManager::GetInstance()->GetHandle("Target");
		glBindTexture(GL_TEXTURE_2D, texture);

		//�I�̏c��
		const float width = 3.0f;
		const float height = 3.0f;

		//�`��ꏊ
		const float value = 30.0f;//�L�����N�^�[�Ƃ̊Ԋu�⊮�l
		glm::vec3 v;
		glm::vec3 pos = m_transform.m_position;
		glm::vec3 toVec = m_transform.m_myToVec*value;

		v = pos + toVec;

		/*v.x = m_transform.GetPosition().x - sin(m_transform.GetRotation().y)*value;
		v.y = m_transform.GetPosition().y + sin(m_transform.GetRotation().x)*value;
		v.z = m_transform.GetPosition().z - cos(m_transform.GetRotation().y)*value;*/

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glPushMatrix();
		{
			glTranslatef(v.x, v.y, v.z);

			//�r���{�[�h��]�s��K�p
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