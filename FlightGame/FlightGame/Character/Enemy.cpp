#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"
#include"../glut.h"

//debug
#include"../MyLibrary/Manager/CharacterManager.h"

//-------------------------------------
//敵のAI

void Enemy::Control()
{
	MoveToAimPos();
	//SetYaw();
	//SetPitch();

	m_value += 0.00001f*(M_PI / 180);//変更予定

	if (m_value >= 1.0f)
	{
		m_value = 1.0f;
	}

	//ここ？
	if (CheckNearAimPis())
	{
		ResetAimPos();
	}

	//debug
	//DrawAimPos();
	//DrawToAimVec();
}

//-------------------------------------
//一点座標を決めてそこに向かって移動する

void Enemy::MoveToAimPos()
{	
	//自分の座標から目標点への向きベクトル
	glm::vec3 vec = m_aimPos - m_transform.GetPosition();
	vec = glm::normalize(vec);

	//スピードの設定
	m_speed = vec*0.2f;

}

//-------------------------------------
//ヨー回転処理

void Enemy::SetYaw()
{
	//自身の座標と向けたい方向のベクトルとの差分
	glm::vec3 dif = m_aimPos - m_transform.GetPosition();

	//移動の補完値

	dif = dif * m_value;

	float x = (m_transform.m_myToVec + dif).x;
	float z = (m_transform.m_myToVec + dif).z;
	float yaw = atan2f(-x, -z);
	m_transform.SetRotationY(yaw);

}

//-------------------------------------
//ピッチ回転処理

void Enemy::SetPitch()
{
	//向きベクトルと向けたい方向のベクトルとの差分
	glm::vec3 dif = - m_transform.GetPosition();

	//移動の補完値

	dif = dif * m_value;

	float y = (m_transform.m_myToVec + dif).y;
	float z = (m_transform.m_myToVec + dif).z;
	float pitch = atan2f(-y, -z);
	m_transform.SetRotationX(pitch);

}

//-------------------------------------
//目標点と自身の距離が一定値以内ならtrue
//一定値外であればfalseを返す

bool Enemy::CheckNearAimPis()const
{
	glm::vec3 v;
	v = m_aimPos - m_transform.GetPosition();

	//距離の一定値
	const float value = 5.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//目標点の再設定

void Enemy::ResetAimPos()
{
	const float x_max = 256.0f;
	m_aimPos.x = ((float)rand() / RAND_MAX)*x_max;

	const float bottom = 5.0f;
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
			glm::vec3 root = m_transform.GetPosition();
			glVertex3f(root.x, root.y, root.z);

			glm::vec3 aim = m_aimPos;
			glVertex3f(aim.x, aim.y, aim.z);
		}
		glEnd();
	}
	glPopAttrib();
}