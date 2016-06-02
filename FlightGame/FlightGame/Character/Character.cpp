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
//コンストラクタ

Character::Character()
{
	m_transform.m_scale = glm::vec3(0.3f, 0.6f, 0.3f);

	//体部分
	oka::ModelSP body = oka::ModelManager::GetInstance()->m_models["Body"];
	unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("FlyTex"));
	m_body = oka::Mesh::Create(body, tex);
	oka::GameManager::GetInstance()->Add("Body", m_body);

	//プロペラ部分
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
	//座標更新
	m_speed += m_accel;
	m_transform.m_position += m_speed;

	//慣性
	m_speed *= 0.965f;

	//ボディ
	m_body->m_transform = m_transform;

	//オフセット計算
	glm::mat4 offSet;
	
	const glm::mat4 translate = glm::translate(glm::vec3(0.0f, 0.3f, -5.2f));
	
	//static float angle = 0.0f;
	//angle += oka::MyMath::ToRadian(2.0f);
	//const glm::vec3 axis = glm::vec3(0, 1, 0);
	//const glm::mat4 rotate = glm::rotate(angle, axis);

	const glm::mat4 scale = glm::scale(glm::vec3(2, 2, 2));

	offSet = translate*scale;

   //プロペラ
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
		//書き換え
		m_hp -= 100;
	}

	m_isHitAttack = false;


//debug
glm::vec3 pos = m_transform.m_position;
//printf("x:%f,y:%f,z:%f\n", pos.x, pos.y, pos.z);



	//フィールドとの判定
	if (IsGroundOut())
	{
//debug
//printf("出てるよおおおおおおおおおお\n");
	}
	else
	{
		if (IsIntersectGround())
		{
//debug
//printf("地面に当たってるよおおおおおおおお\n");
			m_hp = 0;
		}
	}

	//死亡判定
	if (m_isActive)
	{
		if (IsDead())
		{
			m_isActive = false;
			m_body->m_isActive = false;
			m_propeller->m_isActive = false;
			
			//爆発音
			oka::SoundManager::GetInstance()->Play("Explode");

			//爆発エフェクト
			const unsigned int num = 15;
			oka::GameManager::GetInstance()->Add("Smoke", Smoke::Create(m_transform.m_position, num));
			oka::GameManager::GetInstance()->Add("Fire", Fire::Create(m_transform.m_position));
		}
	}
}

//-------------------------------------
//ゲームパッドでの操作

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
//前進処理
//ゲームパッド A で前進

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
//弾による攻撃

void Character::Shot(unsigned short _downKeys)
{
	if (_downKeys & XINPUT_GAMEPAD_Y)
	{
		oka::SoundManager::GetInstance()->Play("Shot");

		glm::vec3 pos;
		const float distance = 2.0f;//自機と弾発射点の間隔
		pos = m_transform.m_position + m_transform.m_myToVec*distance;

		glm::vec3 speed;
		const float value = 4.0f;//弾のスピード補完値
		speed = m_transform.m_myToVec * value;

		glm::mat4 mat = m_transform.m_rotate;

		BulletSP bullet = Bullet::Create(pos, mat, speed);
		oka::BulletManager::GetInstance()->Add(bullet);
		oka::GameManager::GetInstance()->Add("Bullet", bullet);
	}
}

//-------------------------------------
//地形部分内にいるか外にいるかの判定

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
//フィールドとの衝突判定
//各フィールド頂点のy座標値と
//自身のy座標値で比較する

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
//HPの値を参照し0以下になっていればtrue
//そうでなければfalseを返す

bool Character::IsDead()const
{
	if (m_hp <= 0)
	{	
		return true;
	}

	return false;
	
}
