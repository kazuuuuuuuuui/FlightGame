#define _USE_MATH_DEFINES
#include<math.h>
#include"Character.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/ModelManager.h"
#include"../MyLibrary/Input/Keyboard.h"
#include"../Effect/Smoke.h"
#include"../Effect/Fire.h"

#include"../glut.h"

void Character::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			//行列適応
			glMultMatrixf((GLfloat*)&m_matrix);

			glutSolidTeapot(1);
		}
		glPopMatrix();
	}
	glPopAttrib();

	/*glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glPushMatrix();
		{
			glMultMatrixf((GLfloat*)&m_matrix);

			auto v = m_body->m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_body->m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto i = m_body->m_index.begin();

			glDrawElements(GL_TRIANGLES, m_indeces * 3, GL_UNSIGNED_SHORT, &(*i));

		}
		glPopMatrix();

	}
	glPopAttrib();*/

}

void Character::Update()
{
	if (m_isHitAttack)
	{
		//書き換え
		m_hp -= 5;
	}

	m_isHitAttack = false;


	//行列計算

	//translate
	m_translate = glm::mat4(1.0);
	m_translate = glm::translate(m_translate,m_transform.GetPosition());

	//scale
	m_scale = glm::mat4(1.0);
	m_scale = glm::scale(m_scale,m_transform.GetScale());

	//行列乗算
	m_matrix = glm::mat4(1.0f);
	m_matrix = m_translate * m_rotate * m_scale;

	//座標更新
	m_speed += m_accel;
	m_transform.SetPosition(m_transform.GetPosition() + m_speed);

	//慣性
	m_speed *= 0.965f;

	//死亡判定
	if (CheckIsDead())
	{
		m_isActive = false;

		//爆発エフェクト
		/*oka::GameManager::GetInstance()->AddGameObject("Smoke", Smoke::Create(m_transform.GetPosition()));
		oka::GameManager::GetInstance()->AddGameObject("Fire", Fire::Create(m_transform.GetPosition()));*/
	}


	//debug
	m_transform.DrawMyToVec();
	//m_transform.DrawMyUpVec();
}

//-------------------------------------
//HPの値を参照し0以下になっていればtrue
//そうでなければfalseを返す

bool Character::CheckIsDead()const
{
	if (m_hp <= 0)
	{	
		return true;
	}

	return false;
	
}
