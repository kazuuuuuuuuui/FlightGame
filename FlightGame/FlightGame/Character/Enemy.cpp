#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/BulletManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
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
//敵のAI

void Enemy::Control()
{
	//変えたい
	const auto characterTop = oka::CharacterManager::GetInstance()->m_characters.begin();

	const glm::vec3 pos = m_transform.m_position;
	const glm::vec3 dir = m_transform.m_myToVec;
	const glm::vec3 aimPos = (*characterTop)->m_transform.m_position;
	const float rad = 100.0f;
	float distance;


	//printf("%d\n", m_flame);

	if (glm::intersectRaySphere(pos, dir, aimPos, rad, distance))
	{

		//5秒に1回弾発射
		if (0 == (m_flame % (60 * 5)))
		{
			printf("aaa\n");
			//glm::vec3 pos;
			//const float distance = 2.0f;//自機と弾発射点の間隔
			//pos = m_transform.m_position + m_transform.m_myToVec*distance;

			//glm::vec3 speed;
			//const float value = 1.0f;//弾のスピード補完値
			//speed = m_transform.m_myToVec * value;

			//glm::mat4 mat = m_transform.m_rotate;

			//BulletSP bullet = Bullet::Create(pos, mat, speed);
			//oka::BulletManager::GetInstance()->Add(bullet);
			//oka::GameManager::GetInstance()->Add("Bullet", bullet);
		}
	}
	//debug
	else
	{
		//printf("x:%f,y:%f,z:%f\n", aimPos.x, aimPos.y, aimPos.z);
	}



	
	/*glm::vec3 v = m_aimPos - m_transform.m_position;

	if (glm::length(v) <= 5.0f)
	{
		ResetAimPos();
	}

	v = glm::normalize(v);
	v *= 0.01f;
	m_accel = v;*/

	

//printf("x:%f,y:%f,z:%f\n", m_transform.m_position.x, m_transform.m_position.y, m_transform.m_position.z);

	//debug
	//DrawAimPos();
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


//-------------------------------------
//debug

//-------------------------------------
//目指している座標点可視化

void Enemy::DrawAimPos()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glColor3f(1.0f, 0.0f, 0.0f);

		glPushMatrix();
		{
			glTranslatef(m_aimPos.x, m_aimPos.y, m_aimPos.z);
			glutSolidCube(1);
		}
		glPopMatrix();

	}
	glPopAttrib();
}

//-------------------------------------
//目指している座標点への方向ベクトル可視化

void Enemy::DrawToAimVec()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glLineWidth(3.0f);
		glColor3f(1.0f, 1.0f, 0.0f);

		glBegin(GL_LINES);
		{
			glm::vec3 root = m_transform.m_position;
			glVertex3f(root.x, root.y, root.z);

			glm::vec3 aim = m_aimPos;
			glVertex3f(aim.x, aim.y, aim.z);
		}
		glEnd();
	}
	glPopAttrib();
}