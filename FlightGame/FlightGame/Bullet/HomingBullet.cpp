#include"HomingBullet.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../Effect/EffectInfo.h"
#include"../Effect/Smoke.h"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

HomingBullet::HomingBullet(glm::vec3 *_target,glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed)
{
	//debug
	//printf("ホーミング弾が生成されました\n");
	m_isHoming = true;
	m_target = _target;
	m_originPos = _pos;
	m_transform.m_position = _pos;
	m_transform.m_rotate = _rotate;
	m_speed = _speed;

}

//-------------------------------------
//デストラクタ

HomingBullet::~HomingBullet()
{
	//debug
	//printf("弾が削除されました\n");
}

//-------------------------------------
//弾の生成

HomingBulletSP HomingBullet::Create(glm::vec3 *_target,glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed)
{
	HomingBulletSP bullet(new HomingBullet(_target, _pos, _rotate, _speed));

	return bullet;
}

//-------------------------------------
//描画

void HomingBullet::Draw()
{
	glPushMatrix();
	{
		//行列適応
		glMultMatrixf((GLfloat*)&m_transform.m_matrix);

		glutWireSphere(0.5, 10, 10);
	}
	glPopMatrix();
}

//-------------------------------------
//更新

void HomingBullet::Update()
{	
	if (0 == m_flame % 30)
	{
		m_isHoming = false;
	}

	if (m_isHoming)
	{
		SetHomingSpeed();
	}

	m_transform.m_position += m_speed;

	//関数化した方がいい？
	if (0 == m_flame % 2)
	{
		EffectInfo info;
		info.basePos = m_transform.m_position;
		info.particleNum = 1;
		info.color = glm::vec3(230.0f / 255.0f, 230.0f / 255.0f, 230.0f / 255.0f);
		SmokeSP smoke = Smoke::Create(info);
		oka::GameManager::GetInstance()->Add("Smoke", smoke);
	}

	//ある程度の距離離れたら非活性にする
	const float distance = 500;
	if (glm::length(m_transform.m_position - m_originPos) >= distance)
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

bool HomingBullet::IsHit(glm::vec3 _pos)const
{
	glm::vec3 v;
	v = m_transform.m_position - _pos;

	//弾とキャラクターとの距離
	const float value = 5.0f;
	float distance = glm::length(v);

	if (distance <= value)
	{
		return true;
	}

	return false;

}

//-------------------------------------
//ホーミング速度の設定

void HomingBullet::SetHomingSpeed()
{
	glm::vec3 v1 = m_transform.m_myToVec;
	glm::vec3 v2 = *(m_target) - m_transform.m_position;

	glm::vec3 dir = (v2 - v1);
	dir = glm::normalize(dir);
	dir *= 0.5f;

	m_speed += dir;
}
