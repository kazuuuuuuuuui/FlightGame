#include"Bullet.h"
#include"../MyLibrary/Manager/CharacterManager.h"
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
