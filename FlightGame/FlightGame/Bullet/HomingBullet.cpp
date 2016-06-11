#include"HomingBullet.h"
#include"../MyLibrary/Manager/CharacterManager.h"
#include"../glut.h"

//-------------------------------------
//コンストラクタ

HomingBullet::HomingBullet(glm::vec3 _targetPos,glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed)

{
	//debug
	printf("ホーミング弾が生成されました\n");

	m_targetPos = _targetPos;
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

HomingBulletSP HomingBullet::Create(glm::vec3 _targetPos,glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed)
{
	HomingBulletSP bullet(new HomingBullet(_targetPos, _pos, _rotate, _speed));

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
	/*glm::vec3 v1 = glm::normalize(m_targetPos);
	glm::vec3 v2 = glm::normalize(m_transform.m_position + m_transform.m_myToVec);
	glm::vec3 dir = (v1 - v2)*0.01f;

	m_speed += dir;

	m_transform.m_position += m_speed;*/

	////ある程度の距離離れたら非活性にする
	//const float distance = 500;
	////printf("%f\n", glm::length(m_transform.m_position - m_originPos));

	//if (glm::length(m_transform.m_position - m_originPos) >= distance)
	//{
	//	m_isActive = false;
	//}

	////フィールド内にいるか
	//if (!IsGroundOut())
	//{
	//	if (IsIntersectGround())
	//	{
	//		//oka::GameManager::GetInstance()->Add("Smoke", Smoke::Create(m_transform.m_position));
	//		//m_isActive = false;
	//	}
	//}

	////キャラクターとの当たり判定
	//auto itr = oka::CharacterManager::GetInstance()->m_characters.begin();
	//auto end = oka::CharacterManager::GetInstance()->m_characters.end();

	//while (itr != end)
	//{
	//	const glm::vec3 pos = (*itr)->m_transform.m_position;

	//	if (IsHit(pos))
	//	{
	//		(*itr)->m_isHitAttack = true;
	//		m_isActive = false;
	//	}

	//	itr++;
	//}
}
