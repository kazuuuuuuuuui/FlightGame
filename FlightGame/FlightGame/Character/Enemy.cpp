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
#include"../Effect/Fire.h"
#include"../Effect/Smoke.h"
#include"../glm/gtx/transform.hpp"
#include"../glm/gtx/intersect.hpp"
#include"../glut.h"


glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest) 
{
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	glm::vec3 rotationAxis = glm::cross(start, dest);
	float angle = glm::length(rotationAxis);

	//回転軸がないときは何もしない
	if (angle < 0.1f)
	{
		return glm::angleAxis(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));//何もしないので回転軸は何でもいい
	}
	
	return glm::angleAxis(angle, glm::normalize(rotationAxis));
}

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

	//m_transform.m_position = glm::vec3(0.0f, 30.0f, 0.0f);

	//m_aimPos = glm::vec3(0.0f, 100.0f, -100.0f);

	m_aimPos = m_transform.m_position;
}

//-------------------------------------
//敵の生成

EnemySP Enemy::Create()
{
	EnemySP enemy(new Enemy());

	return enemy;
}

void Enemy::Draw()
{
	/*glPushMatrix();
	{
		glTranslatef(m_aimPos.x, m_aimPos.y, m_aimPos.z);

		glutSolidTeapot(1);
	}
	glPopMatrix();*/
}

//-------------------------------------
//更新

void Enemy::Update()
{
	//座標更新
	m_speed = m_transform.m_myToVec*0.2f + m_accel;
	m_transform.m_position += m_speed;

	SetOnRadarPos();

	//慣性
	//m_accel *= 0.98f;
	//m_speed *= 0.98f;

	const float length = glm::length(m_aimPos - m_transform.m_position);
	
	if (length < 10.0f)
	{
		ResetAimPos();
	}

	//ボディ
	m_body->m_transform = m_transform;

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
	if (!m_isActive)
	{
		//爆発音
		oka::SoundManager::GetInstance()->Play("Explode");

		//爆発エフェクト
		EffectInfo smokeInfo;
		smokeInfo.basePos = m_transform.m_position;
		smokeInfo.particleNum = 5;
		smokeInfo.color = glm::vec3(0, 0, 0);
		SmokeSP smoke = Smoke::Create(smokeInfo);
		oka::GameManager::GetInstance()->Add("Smoke", smoke);

		EffectInfo fireInfo;
		fireInfo.basePos = m_transform.m_position;;
		fireInfo.particleNum = 20;
		fireInfo.color = glm::vec3(1.0f, 0.5f, 0.25f);
		FireSP fire = Fire::Create(fireInfo);
		oka::GameManager::GetInstance()->Add("Fire", fire);

		oka::CharacterManager::GetInstance()->m_player->PlusMyScore();

	}
}

//-------------------------------------
//前方にplayerがいるか判定する
//引数としてplayerの座標をもらう

bool Enemy::IsFrontPlayer(glm::vec3 pos)const
{
	static float dis = 80.0f;

	if (IsNear(pos, dis))
	{
		const glm::vec3 pos = m_transform.m_position;
		const glm::vec3 dir = m_transform.m_myToVec;
		const glm::vec3 aimPos = oka::CharacterManager::GetInstance()->m_player->m_transform.m_position;
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
			const glm::vec3 v = m_transform.m_position - oka::CharacterManager::GetInstance()->m_player->m_transform.m_position;
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
			oka::BulletManager::GetInstance()->AddBullet(bullet);
			oka::GameManager::GetInstance()->Add("Bullet", bullet);
		}
	}
}

//-------------------------------------
//敵のAI

void Enemy::Control()
{
	/*glm::vec3 v = m_transform.m_position + m_transform.m_myToVec;

	float dy = m_aimPos.y - v.y;
	dy = abs(dy);

	float dz = m_aimPos.z - v.z;
	dz = abs(dz);
	
	float angle = atan2f(dy, dz);
	angle = glm::degrees(angle);
printf("%f\n", angle);

	if (angle > 5.0f)
	{
		m_Controller.m_stickDown = true;
	}
	else
	{
		m_Controller.m_stickDown = false;
	}*/


	//const float value = oka::MyMath::ToRadian(0.8f);
	//glm::tquat<float> quat;

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
	/*if (m_Controller.m_stickUp)
	{
		quat = oka::MyMath::Rotate(-value, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}
	else if (m_Controller.m_stickDown)
	{
		quat = oka::MyMath::Rotate(value, glm::vec3(1, 0, 0));

		m_transform.m_rotate *= quat;
	}*/



	if (nullptr != oka::CharacterManager::GetInstance()->m_player)
	{
		const glm::vec3 pos = oka::CharacterManager::GetInstance()->m_player->m_transform.m_position;

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

		m_accel = accel*0.02f;
		
		glm::vec3 start = m_transform.m_myToVec;
		glm::vec3 dest = accel;

		glm::tquat<float>quat = RotationBetweenVectors(start, dest);
		m_transform.m_rotate = quat * m_transform.m_rotate;
	}
}

//-------------------------------------
//playerの追跡

void Enemy::Chase()
{
	const glm::vec3 aimPos = oka::CharacterManager::GetInstance()->m_player->m_transform.m_position;
	glm::vec3 v = aimPos - m_transform.m_position;

	float length = glm::length(v);
	const float distance = 30.0f;

	v = glm::normalize(v);

	//近すぎたら止まる
	if (length < distance)
	{
		m_accel = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		v *= 0.05f;
		m_accel = v;	
	}

	glm::vec3 start = m_transform.m_myToVec;
	glm::vec3 dest = v;

	glm::tquat<float>quat = RotationBetweenVectors(start, dest);
	m_transform.m_rotate = quat * m_transform.m_rotate;
}

//-------------------------------------
//弾と接触した際の墜落処理

void Enemy::Fall()
{
	const glm::tquat<float> quat = oka::MyMath::Rotate(oka::MyMath::ToRadian(3.0f), glm::vec3(0, 0, -1));
	m_transform.m_rotate *= quat;

	//m_accel = glm::vec3(0.0f, 0.0f, 0.0f);

	m_transform.m_position.y -= 0.5f;

	if (0 == (m_flame % 5))
	{
		EffectInfo info;
		info.basePos = m_transform.m_position;
		info.particleNum = 1;
		info.color = glm::vec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f);

		SmokeSP smoke = Smoke::Create(info);
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
