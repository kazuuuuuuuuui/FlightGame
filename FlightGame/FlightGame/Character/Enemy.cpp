#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"
#include"../MyLibrary/Math/MyMath.h"
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
//コンストラクタ

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
//敵の生成

EnemySP Enemy::Create(glm::vec3 _pos)
{
	EnemySP enemy(new Enemy(_pos));

	return enemy;
}

//-------------------------------------
//更新

void Enemy::Update()
{
	static float speed = -0.1f;
	m_speed.z = speed;

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

	const glm::mat4 scale = glm::scale(glm::vec3(2, 2, 2));

	offSet = translate*scale;

	//プロペラ
	m_propeller->m_transform = m_transform;
	m_propeller->m_transform.m_matrix = m_transform.m_matrix * offSet;


	Control();


	if (m_isHitAttack)
	{
		m_transform.m_rotate *= oka::MyMath::Rotate(oka::MyMath::ToRadian(3.0f), m_transform.m_myToVec);
		
		m_speed.y = -0.1f;

		if (0 == (m_flame % 40))
		{
			EffectInfo info;
			info.basePos = m_transform.m_position;
			info.particleNum = 2;
			info.color = glm::vec3(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f);

			SmokeSP smoke = Smoke::Create(info);
			oka::GameManager::GetInstance()->Add("Smoke", smoke);
		}
	}

	//debug
	//glm::vec3 pos = m_transform.m_position;
	//printf("x:%f,y:%f,z:%f\n", pos.x, pos.y, pos.z);

	if (IsGroundOut())
	{
		if (IsIntersectSea())
		{
			m_hp = 0;
		}
	}
	else
	{
		SetOnRadarPos();

		if (IsIntersectGround())
		{
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
			EffectInfo info;
			info.basePos = m_transform.m_position;
			info.particleNum = 10;
			info.color = glm::vec3(0, 0, 0);

			SmokeSP smoke = Smoke::Create(info);
			oka::GameManager::GetInstance()->Add("Smoke", smoke);
		}
	}
}

//-------------------------------------
//弾による攻撃

void Enemy::Shot()
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

	glm::mat4 mat = m_transform.m_rotate;

	BulletSP bullet = Bullet::Create(pos, mat, speed);
	oka::BulletManager::GetInstance()->AddBullet(bullet);
	oka::GameManager::GetInstance()->Add("Bullet", bullet);
}

//-------------------------------------
//敵のAI

void Enemy::Control()
{
	const glm::vec3 pos = m_transform.m_position;
	const glm::vec3 dir = m_transform.m_myToVec;
	const glm::vec3 aimPos = oka::CharacterManager::GetInstance()->m_player->m_transform.m_position;
	const float rad = 50.0f;
	float distance;

	if (glm::intersectRaySphere(pos, dir, aimPos, rad, distance))
	{
		//20Fに1回弾発射
		if (0 == (m_flame % 10))
		{
			Shot();
		}
	}
}

//-------------------------------------
//目標点の再設定

void Enemy::ResetAimPos()
{
	const float x_max = 256.0f;
	m_aimPos.x = ((float)rand() / RAND_MAX)*x_max;

	const float bottom = 20.0f;
	m_aimPos.y = bottom + ((float)rand() / RAND_MAX)*10.0f;

	const float z_max = -256.0f;
	m_aimPos.z = ((float)rand() / RAND_MAX)*z_max;
}