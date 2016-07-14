#include"Bullet.h"
#include"../MyLibrary/Manager/GameManager.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../MyLibrary/Manager/ImageManager.h"
#include"../Effect/Smoke.h"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

Bullet::Bullet(glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed)
{
	m_originPos = _pos;
	m_transform.m_position = _pos;
	m_transform.m_rotate = _rotate;
	m_speed = _speed;

}

//-------------------------------------
//デストラクタ

Bullet::~Bullet()
{
	
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
		float diffuse[] = { 255.0f / 255.0f,255.0f / 255.0f,0.0f / 255.0f,1.0f };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		
		glPushMatrix();
		{
			glMultMatrixf((GLfloat*)&m_transform.m_matrix);

			glScalef(0.1f, 0.1f, 2.0f);

			glutSolidSphere(1.0, 10, 10);
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
			SmokeSP smoke = Smoke::Create(m_transform.m_position, 1, glm::vec3(211.0f / 255.0f, 183.0f / 255.0f, 138.0f / 255.0f));
			oka::GameManager::GetInstance()->Add("Smoke", smoke);

			m_isActive = false;
		}
	}

	//キャラクターとの当たり判定
	auto itr = oka::CharacterManager::GetInstance()->GetCharacters()->begin();
	auto end = oka::CharacterManager::GetInstance()->GetCharacters()->end();

	while (itr != end)
	{
		const glm::vec3 pos = (*itr)->m_transform.m_position;

		if (IsHit(pos))
		{
			(*itr)->SetIsHitAttack(true);
			m_isActive = false;
		}

		itr++;
	}	
}