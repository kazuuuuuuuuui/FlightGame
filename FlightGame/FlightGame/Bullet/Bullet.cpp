#include"Bullet.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../Effect/EffectInfo.h"
#include"../Effect/Smoke.h"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

Bullet::Bullet(glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed)
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

BulletSP Bullet::Create(glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed)
{
	BulletSP bullet(new Bullet(_pos, _rotate, _speed));

	return bullet;
}

//-------------------------------------
//描画

void Bullet::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glPushMatrix();
		{
			glMultMatrixf((GLfloat*)&m_transform.m_matrix);

			glScalef(1, 1, 10);

			glutSolidSphere(0.2, 10, 10);
		}
		glPopMatrix();
	}
	glPopAttrib();
}

//-------------------------------------
//更新

void Bullet::Update()
{
	m_transform.m_position += m_speed;

	//ある程度の距離離れたら非活性にする
	const float distance = 500;
	if (glm::length(m_transform.m_position - m_originPos) >= distance )
	{
		m_isActive = false;
	}


	if (IsGroundOut())
	{
		if (IsIntersectSea())
		{
			m_isActive = false;
		}
	}
	else
	{
		if (IsIntersectGround())
		{
			EffectInfo info;
			info.basePos = m_transform.m_position;
			info.particleNum = 1;
			info.color = glm::vec3(211.0f / 255.0f, 183.0f / 255.0f, 138.0f / 255.0f);

			SmokeSP smoke = Smoke::Create(info);
			oka::GameManager::GetInstance()->Add("Smoke", smoke);

			m_isActive = false;
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
	const float value = 3.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;

}
