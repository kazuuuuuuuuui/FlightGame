#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"../MyLibrary/Input/Controller.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
//#include"../Effect/Smoke.h"
#include"../MyLibrary/Manager/EffectManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Camera/Camera.h"

#include"../glm/glm.hpp"
#include"../glm/gtc/matrix_transform.hpp"

#include"../glm/gtc/quaternion.hpp"
#include"../glm/gtx/quaternion.hpp"

#include"../glut.h"

//-------------------------------------
//�L�[�{�[�h�ł̑���

void Player::Control()
{
	Accel();
	Yaw();
	Roll();

	Shot();

	const float value = 0.4f * ((float)M_PI / 180.0f);


	//�㏸
	if (oka::Keyboard::GetStates('s'))
	{
		m_transform.SetRotationX(m_transform.GetRotation().x + value);
	}

	//���~
	else if (oka::Keyboard::GetStates('w'))
	{
		m_transform.SetRotationX(m_transform.GetRotation().x - value);
	}

	//���̎p���ɖ߂�
	else
	{
		//.SetRotationX(m_transform.GetRotation().m_x - (m_transform.GetRotation().m_x)*0.1f);
	}
}

//-------------------------------------
//�Q�[���p�b�h�ł̑���

void Player::Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY)
{
	Accel(_pressedKey);

	glm::vec3 nowRotate = m_transform.GetRotation();

	const float value = oka::MyMath::ToRadian(1.0f);

	//Roll
	if (_pressedKey & XINPUT_GAMEPAD_B)
	{
		m_transform.SetRotationZ(nowRotate.z + value);
		Rotate(value, m_transform.m_myToVec);
	}
	else if(_pressedKey & XINPUT_GAMEPAD_X)
	{
		m_transform.SetRotationZ(nowRotate.z - value);
		Rotate(-value, m_transform.m_myToVec);
	}

	//Yaw
	if (_sThumbLX > 0.3f)
	{
		_sThumbLX = 1.0f;
		m_transform.SetRotationY(nowRotate.y - value);
		Rotate(-value, m_transform.m_myUpVec);
	}
	else if (_sThumbLX < -0.3f)
	{
		_sThumbLX = -1.0f;
		m_transform.SetRotationY(nowRotate.y + value);
		Rotate(+value, m_transform.m_myUpVec);
	}
	
	//Pitch
	if (_sThumbLY > 0.3f)
	{
		_sThumbLY = 1.0f;
		m_transform.SetRotationX(nowRotate.x + value);
		Rotate(value, m_transform.m_mySideVec);
	}
	else if (_sThumbLY < -0.3f)
	{
		_sThumbLY = -1.0f;
		m_transform.SetRotationX(nowRotate.x - value);
		Rotate(-value, m_transform.m_mySideVec);
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
	if (oka::Keyboard::GetStates(' '))
	{
		const float value = -0.05f;//�⊮�W��
		glm::vec3 accel;
		accel.x = value*sin(m_transform.GetRotation().y);
		accel.y = (-1)*value*sin(m_transform.GetRotation().x);
		accel.z = value*cos(m_transform.GetRotation().y);
	}
	else
	{
		m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

//-------------------------------------
//�O�i����
//�Q�[���p�b�h A �őO�i

void Player::Accel(unsigned short _pressedKey)
{
	if (_pressedKey & XINPUT_GAMEPAD_A)
	{
		const float value = -0.05f;
		glm::vec3 accel;
		accel.x = value*sin(m_transform.GetRotation().y);
		accel.y = (-1)*value*sin(m_transform.GetRotation().x);
		accel.z = value*cos(m_transform.GetRotation().y);

		m_accel = accel;

		//�O�i���̉����o
		/*glm::vec3 myPos = m_transform.GetPosition();
		glm::vec3 pos;
		pos.x = myPos.x - sin(m_transform.GetRotation().y);
		pos.y = myPos.y + sin(m_transform.GetRotation().x);
		pos.z = myPos.z - cos(m_transform.GetRotation().y);

		int particleNum = 1;
		oka::EffectManager::GetInstance()->AddEffects(Smoke::Create(pos, particleNum));*/

	}
	else
	{
		m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
	}

}


//-------------------------------------
//��]����
//�����Ƃ��ĉ�]�p�x�Ɖ�]�����󂯂Ƃ�

void Player::Rotate(float _angle, glm::vec3 _axis)
{
	glm::quat quat;
	
	quat.x = _axis.x * sin(_angle / 2);
	quat.y = _axis.y * sin(_angle / 2);
	quat.z = _axis.z * sin(_angle / 2);
	quat.w = cos(_angle / 2);

	quat = glm::quat(quat);
	m_transform.m_rotateMatrix *= glm::toMat4(quat);
}


//-------------------------------------
//�L�[�{�[�h�ɂ�����

void Player::Yaw()
{
	//����̊��炩��
	//const float value = 0.5f*(M_PI / 180.0f);

	////�E����
	//if (oka::Keyboard::GetStates('d'))
	//{
	//	m_transform.SetRotationY(m_transform.GetRotation().y - value);
	//	//m_transform.SetRotationZ(m_transform.GetRotation().m_z + ((-1)*(1.0f / 2.0f) - m_transform.GetRotation().m_z)*0.1f);
	//}

	////������
	//else if (oka::Keyboard::GetStates('a'))
	//{
	//	m_transform.SetRotationY(m_transform.GetRotation().y + value);
	//	//m_transform.SetRotationZ(m_transform.GetRotation().m_z + ((-1)*(-1.0f / 2.0f) - m_transform.GetRotation().m_z)*0.1f);
	//}

	////���̎p���ɖ߂�
	//else
	//{
	//	//m_transform.SetRotationZ(m_transform.GetRotation().m_z - (m_transform.GetRotation().m_z)*0.1f);
	//}

	//glm::vec3 axis;

	//



	//glm::vec4 rotate;
	//float angle = m_transform.GetRotation().y;

	//rotate.x = axis.x * sin(angle / 2);
	//rotate.y = axis.y * sin(angle / 2);
	//rotate.z = axis.z * sin(angle / 2);
	//rotate.w = cos(angle / 2);

	//glm::quat quat = glm::quat(rotate.w, rotate.x, rotate.y, rotate.z);

	////rotate
	//m_transform.m_rotateMatrix = glm::mat4(1.0);
	//m_transform.m_rotateMatrix = glm::toMat4(quat);
}


//-------------------------------------
//�L�[�{�[�h�ɂ�郍�[����]

void Player::Roll()
{
	//const float value = 1.2f * (M_PI / 180);

	////�E���[����]
	//if (oka::Keyboard::GetStates('n'))
	//{
	//	m_transform.SetRotationZ(m_transform.GetRotation().z + value);
	//}

	////�����[����]
	//else if (oka::Keyboard::GetStates('m'))
	//{
	//	m_transform.SetRotationZ(m_transform.GetRotation().z - value);
	//}
}


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
		glm::vec3 pos;
		const float distance = 2.0f;//���@�ƒe���˓_�̊Ԋu
		pos = m_transform.GetPosition()+m_transform.m_myToVec*distance;

		glm::vec3 rotate = m_transform.GetRotation();

		glm::vec3 speed;
		const float value = 1.0f;//�e�̃X�s�[�h�⊮�l

		speed = m_transform.m_myToVec * value;

	if (_downKeys & XINPUT_GAMEPAD_Y)
	{
		oka::SoundManager::GetInstance()->Play("Shot");
		Bullet *bullet = new Bullet(pos, rotate, speed);
		oka::BulletManager::GetInstance()->AddBullet(bullet);
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
		glm::vec3 pos = m_transform.GetPosition();
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