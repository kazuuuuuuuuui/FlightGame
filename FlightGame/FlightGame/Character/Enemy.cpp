#define _USE_MATH_DEFINES
#include<math.h>
#include<random>
#include"Enemy.h"
#include"../MyLibrary/Math/MyMath.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/SoundManager.h"
#include"../MyLibrary/Manager/FealdManager.h"
#include"../MyLibrary/Manager/ScoreManager.h"
#include"../Effect/Fire.h"
#include"../Effect/Smoke.h"
#include"../glm/gtx/transform.hpp"
#include"../glm/gtx/intersect.hpp"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

Enemy::Enemy()
{
	static float left = oka::FealdManager::GetInstance()->m_feald->m_leftBottom.x;
	static float right = oka::FealdManager::GetInstance()->m_feald->m_rightBottom.x;
	static float front = oka::FealdManager::GetInstance()->m_feald->m_leftBottom.z;
	static float back = oka::FealdManager::GetInstance()->m_feald->m_rightTop.z;

	std::random_device rnd;
	std::mt19937 mt(rnd());	
	std::uniform_int_distribution<> x(left, right);
	std::uniform_int_distribution<> y(50, 100);
	std::uniform_int_distribution<> z(back, front);

	m_transform.m_position.x = x(mt);
	m_transform.m_position.y = y(mt);
	m_transform.m_position.z = z(mt);

	m_aimPos = m_transform.m_position;
}

//-------------------------------------
//敵の生成

EnemySP Enemy::Create()
{
	EnemySP enemy(new Enemy());

	return enemy;
}

//-------------------------------------
//更新

void Enemy::Update()
{
	//座標更新
	//m_speed = m_transform.m_myToVec*0.1f;
	m_speed += m_accel;
	m_transform.m_position += m_speed;

	SetOnRadarPos();

	//慣性
	m_accel *= 0.98f;
	m_speed *= 0.98f;

	const float length = glm::length(m_aimPos - m_transform.m_position);
	
	if (length < 10.0f)
	{
		ResetAimPos();
	}

	//ボディ
	m_body->m_transform = m_transform;

	////煙
	//if (0 == m_flame % 3)
	//{
	//	EffectInfo info;
	//	info.basePos = m_transform.m_position - m_transform.m_myUpVec*0.5f;
	//	info.particleNum = 1;
	//	info.color = glm::vec3(195.0f / 255.0f, 195.0f / 255.0f, 195.0f / 255.0f);
	//	SmokeSP smoke = Smoke::Create(info);
	//	oka::GameManager::GetInstance()->Add("Smoke", smoke);
	//}

	/*書き換える*/
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

	Control();

	if (m_isHitAttack)
	{
		Fall();
	}

	if (IsGroundOut())
	{
		if (IsIntersectSea())
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

	//死亡判定
	if (false == m_isActive)
	{
		//爆発音
		oka::SoundManager::GetInstance()->Play("Explode");

		//爆発エフェクト
		SmokeSP smoke = Smoke::Create(m_transform.m_position, 5, glm::vec3(0.0f, 0.0f, 0.0f));
		oka::GameManager::GetInstance()->Add("Smoke", smoke);

		FireSP fire = Fire::Create(m_transform.m_position, 20, glm::vec3(1.0f, 0.5f, 0.25f));
		oka::GameManager::GetInstance()->Add("Fire", fire);

		oka::ScoreManager::GetInstance()->PlusScore();
	}
}

//-------------------------------------
//前方にplayerがいるか判定する
//引数としてplayerの座標をもらう

bool Enemy::IsFrontPlayer(glm::vec3 pos)const
{
	static float dis = 50.0f;

	if (IsNear(pos, dis))
	{
		const glm::vec3 pos = m_transform.m_position;
		const glm::vec3 dir = m_transform.m_myToVec;
		const glm::vec3 aimPos = oka::CharacterManager::GetInstance()->GetPlayer()->m_transform.m_position;
		const float rad = 100.0f;
		float distance;

		if (glm::intersectRaySphere(pos, dir, aimPos, rad, distance))
		{
			return true;
		}
	}
	
	return false;
}

//-------------------------------------
//弾による攻撃

void Enemy::Shot()
{
	if ( false == m_isHitAttack)
	{
		if (0 == (m_flame % 10))
		{
			const glm::vec3 v = m_transform.m_position - oka::CharacterManager::GetInstance()->GetPlayer()->m_transform.m_position;
			float volume = glm::length(v);
			volume = 20.0f / volume;

			oka::SoundManager::GetInstance()->ChangeVolume("Shot", volume);
			oka::SoundManager::GetInstance()->Play("Shot");

			glm::vec3 pos;
			const float distance = 2.0f;//自機と弾発射点の間隔
			pos = m_transform.m_position + m_transform.m_myToVec*distance;

			glm::vec3 speed;
			const float value = 5.0f;//弾のスピード補完値
			speed = m_transform.m_myToVec * value;

			glm::tquat<float> quat = m_transform.m_rotate;

			BulletSP bullet = Bullet::Create(pos, quat, speed);
			oka::BulletManager::GetInstance()->SetBullet(bullet);
			oka::GameManager::GetInstance()->Add("Bullet", bullet);
		}
	}
}

//-------------------------------------
//敵のAI

void Enemy::Control()
{
	/*
	glm::vec3 v1 = m_transform.m_myToVec;
	glm::vec3 v2 = m_aimPos - m_transform.m_position;
	v2 = glm::normalize(v2);

	float cos = glm::dot(v1, v2);

	printf("%f\n", cos);

	float angle = 0.0f;

	angle = acos(cos);
	angle = glm::degrees(angle);
	
	
	if (angle > 5.0f)
	{
		m_controller.m_stickDown = true;
	}
	else
	{
		m_controller.m_stickDown = false;
	}
	*/

	const float value = glm::degrees(1.0f);
	glm::tquat<float> quat;

	//Roll
	/*if (_pressedKey & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		quat = oka::MyMath::Rotate(-value, glm::vec3(0, 1, 0));

		m_transform.m_rotate *= quat;

	}
	else if (_pressedKey & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		quat = oka::MyMath::Rotate(value, glm::vec3(0, 1, 0));

		m_transform.m_rotate *= quat;
	}*/

	//Yaw
	/*if (_sThumbLX > 0.5f)
	{
		quat = oka::MyMath::Rotate(value, glm::vec3(0, 0, -1));

		m_transform.m_rotate *= quat;

	}
	else if (_sThumbLX < -0.5f) {
		quat = oka::MyMath::Rotate(-value, glm::vec3(0, 0, -1));

		m_transform.m_rotate *= quat;
	}*/

	//Pitch
	/*
	if (m_controller.m_stickUp)
	{
		quat = oka::MyMath::Rotate(-value, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
	else if (m_controller.m_stickDown)
	{
		quat = oka::MyMath::Rotate(value, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
	*/

	//printf("x:%f y:%f z:%f w:%f\n", m_transform.m_rotate.x, m_transform.m_rotate.y, m_transform.m_rotate.z, m_transform.m_rotate.w);


	
	if (nullptr != oka::CharacterManager::GetInstance()->GetPlayer())
	{
		const glm::vec3 pos = oka::CharacterManager::GetInstance()->GetPlayer()->m_transform.m_position;

		if (IsFrontPlayer(pos))
		{
			Chase();
			Shot();
		}
		else
		{
			Patrol();
		}
	}
	else
	{
		Patrol();
	}
	
}

//-------------------------------------
//移動スピードの設定
//被弾していないときのみ更新する

void Enemy::Patrol()
{
	if (false == m_isHitAttack)
	{
		glm::vec3 accel = m_aimPos - m_transform.m_position;
		accel = glm::normalize(accel);

		m_accel = accel*0.01f;
		
		glm::vec3 start = m_transform.m_myToVec;
		glm::vec3 dest = accel;

		glm::tquat<float>quat = oka::MyMath::RotationBetweenVectors(start, dest);
		m_transform.m_rotate = quat * m_transform.m_rotate;
	}
}

//-------------------------------------
//playerの追跡

void Enemy::Chase()
{
	const glm::vec3 aimPos = oka::CharacterManager::GetInstance()->GetPlayer()->m_transform.m_position;
	glm::vec3 v = aimPos - m_transform.m_position;

	float length = glm::length(v);
	const float distance = 100.0f;

	v = glm::normalize(v);

	//近すぎたら止まる
	if (length < distance)
	{
		m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		v *= 0.005f;
		m_accel = v;	
	}

	glm::vec3 start = m_transform.m_myToVec;
	glm::vec3 dest = v;

	glm::tquat<float>quat = oka::MyMath::RotationBetweenVectors(start, dest);
	m_transform.m_rotate = quat * m_transform.m_rotate;
}

//-------------------------------------
//弾と接触した際の墜落処理

void Enemy::Fall()
{
	const glm::tquat<float> quat = oka::MyMath::Rotate(glm::radians(3.0f), glm::vec3(0, 0, -1));
	m_transform.m_rotate *= quat;

	m_transform.m_position.y -= 0.3f;

	if (0 == (m_flame % 5))
	{
		SmokeSP smoke = Smoke::Create(m_transform.m_position, 1, glm::vec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f));
		oka::GameManager::GetInstance()->Add("Smoke", smoke);
	}

}

//-------------------------------------
//目標点の再設定

void Enemy::ResetAimPos()
{
	static float left = oka::FealdManager::GetInstance()->m_feald->m_leftBottom.x;
	static float right = oka::FealdManager::GetInstance()->m_feald->m_rightBottom.x;
	static float front = oka::FealdManager::GetInstance()->m_feald->m_leftBottom.z;
	static float back = oka::FealdManager::GetInstance()->m_feald->m_rightTop.z;

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> x(left, right);
	std::uniform_int_distribution<> y(50, 100);
	std::uniform_int_distribution<> z(back, front);

	m_aimPos.x = x(mt);
	m_aimPos.y = y(mt);
	m_aimPos.z = z(mt);
}
