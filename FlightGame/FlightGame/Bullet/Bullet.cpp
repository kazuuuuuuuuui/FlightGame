#include"Bullet.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/FealdManager.h"
#include"../MyLibrary/../Effect/Smoke.h"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

Bullet::Bullet(glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed)
{
	//debug
	//printf("弾が生成されました\n");

	m_originPos = _pos;
	m_transform.m_position = _pos;
	m_transform.m_rotate = _rotate;
	m_speed = _speed;

}

//-------------------------------------
//デストラクタ

Bullet::~Bullet()
{
	//debug
	//printf("弾が削除されました\n");
}

//-------------------------------------
//弾の生成

BulletSP Bullet::Create(glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed)
{
	BulletSP bullet(new Bullet(_pos, _rotate, _speed));

	return bullet;
}

//-------------------------------------
//描画

void Bullet::Draw()
{
	glPushMatrix();
	{
		//行列適応
		glMultMatrixf((GLfloat*)&m_transform.m_matrix);

		glutSolidCube(0.2);
	}
	glPopMatrix();
}

//-------------------------------------
//更新

void Bullet::Update()
{
	m_transform.m_position += m_speed;

	//ある程度の距離離れたら非活性にする
	const float distance = 500;
//printf("%f\n", glm::length(m_transform.m_position - m_originPos));

	if (glm::length(m_transform.m_position - m_originPos) >= distance )
	{
		m_isActive = false;
	}

	//フィールド内にいるか
	if (!IsGroundOut())
	{
		if (IsIntersectGround())
		{
			//oka::GameManager::GetInstance()->Add("Smoke", Smoke::Create(m_transform.m_position));
			//m_isActive = false;
		}
	}

	//キャラクターとの当たり判定
	auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	while (itr != end)
	{
		const glm::vec3 pos = (*itr)->m_transform.m_position;

		if (IsHit(pos))
		{
			(*itr)->m_isHitAttack = true;
			m_isActive = false;
		}

		itr++;
	}	
}

//-------------------------------------
//弾とキャラクターとの当たり判定
//引数としてキャラクター座標をもらってくる

bool Bullet::IsHit(glm::vec3 _pos)const
{
	glm::vec3 v;
	v = m_transform.m_position - _pos;

	//弾とキャラクターとの距離
	const float value = 2.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;

}

//-------------------------------------
//地形部分内にいるか外にいるかの判定

bool Bullet::IsGroundOut()const
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
//弾と地形との接触判定

bool Bullet::IsIntersectGround()const
{
	const int x = m_transform.m_position.x;
	const float y = m_transform.m_position.y;
	const int z = -m_transform.m_position.z;

	const int width = oka::FealdManager::GetInstance()->m_feald->m_width;

	const float height = oka::FealdManager::GetInstance()->m_feald->m_vertex[z * width + x].y;

	//debug
	//printf("h:%f\n", height);

	if (y <= height)
	{
		return true;
	}

	return false;
}