#define _USE_MATH_DEFINES
#include<math.h>

#include"Bullet.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../glut.h"

Bullet::~Bullet()
{
	printf("弾が削除されました\n");
}

void Bullet::Draw()
{
	//glPushAttrib(GL_ALL_ATTRIB_BITS);
	//{
	//	glEnableClientState(GL_VERTEX_ARRAY);
	//	glEnableClientState(GL_NORMAL_ARRAY);

		glPushMatrix();
		{
			//行列適応
			glMultMatrixf((GLfloat*)&m_transform.m_matrix);

			glutSolidCube(0.5);
			//glutSolidCube(1);

			/*auto v = m_model.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_model.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto i = m_model.m_index.begin();

			glDrawElements(GL_TRIANGLES, m_model.m_indeces * 3, GL_UNSIGNED_SHORT, &(*i));*/

		}
		glPopMatrix();

	//}
	//glPopAttrib();

}

void Bullet::Update()
{
	m_transform.SetPosition(m_transform.GetPosition() + m_speed);

	//キャラクターとの当たり判定
	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while(itr != end)
	{
		glm::vec3 pos = (*itr)->m_transform.GetPosition();

		if (CheckIsHit(pos))
		{
			(*itr)->m_isHitAttack = true;
			m_isActive = false;
		}

		itr++;
	}

	//debug
	//m_transform.Update();
	//m_transform.DrawMyToVec();
	//DrawToEnemyVec();

}

bool Bullet::CheckIsHit(glm::vec3 _pos)const
{
	glm::vec3 v;
	v = m_transform.GetPosition() - _pos;

	//弾とキャラクターとの距離
	const float value = 2.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;

}


/*

HomingBulletの方に移す

*/

void Bullet::Homing(glm::vec3 _pos)
{
	//自身の座標と向けたい方向のベクトルとの差分
	glm::vec3 dif = _pos - m_transform.GetPosition();

	//移動の補完値
	static float val = 0.0f;

	dif = dif * val;

	val += 0.0000001f*(M_PI / 180);//変更予定

	if (val >= 1.0f)
	{
		val = 1.0f;
	}

	float x = (m_transform.m_myToVec + dif).x;
	float z = (m_transform.m_myToVec + dif).z;
	float yaw = atan2f(-x, -z);
	m_transform.SetRotationY(yaw);

	float value = 0.005f;//弾のスピード補完値
	m_speed.x = -sin(m_transform.GetRotation().y) * value*(180.0f / M_PI);
	m_speed.y = sin(m_transform.GetRotation().x)* value*(180.0f / M_PI);
	m_speed.z = -cos(m_transform.GetRotation().y) * value*(180.0f / M_PI);

}

bool Bullet::CheckNearCharacter(glm::vec3 _pos)const
{
	glm::vec3 v = _pos - m_transform.GetPosition();
	float distance = glm::length(v);

	const float value = 25.0f;//弾と目標物の間隔

	if (distance <= value)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//debug

void Bullet::DrawToEnemyVec()
{
	/*glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glLineWidth(3.0f);
		glColor3f(1.0f, 0.0f, 1.0f);

		glBegin(GL_LINES);
		{
			glm::vec3 root = m_transform.GetPosition();
			glVertex3f(root.x, root.y, root.z);

			glm::vec3 aim = oka::CharacterManager::GetInstance()->m_characters[1]->m_transform.GetPosition();
			glVertex3f(aim.x, aim.y, aim.z);
		}
		glEnd();
	}
	glPopAttrib();*/

}