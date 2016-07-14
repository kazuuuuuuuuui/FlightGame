#include"BaseBullet.h"
#include"../MyLibrary/Manager/FealdManager.h"

//-------------------------------------
//地形部分内にいるか外にいるかの判定

bool BaseBullet::IsGroundOut()const
{
	//x
	const int width = oka::FealdManager::GetInstance()->m_feald->GetWidth();
	const float x = m_transform.m_position.x;

	if (x <= 0 || width <= x)
	{
		return  true;
	}

	//z
	const int height = oka::FealdManager::GetInstance()->m_feald->GetWidth();
	const float z = m_transform.m_position.z;

	if (z <= -height || 0 <= z)
	{
		return  true;
	}

	return false;
}

//-------------------------------------
//弾と地形との接触判定

bool BaseBullet::IsIntersectGround()const
{
	const int x = (int)m_transform.m_position.x;
	const float y = m_transform.m_position.y;
	const int z = -(int)m_transform.m_position.z;

	const int width = oka::FealdManager::GetInstance()->m_feald->GetWidth();
	const float height = oka::FealdManager::GetInstance()->m_feald->m_vertex[z * width + x].y;

	if (y <= height)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//海との衝突判定
//海の海抜(y座標0)と
//自身のy座標値で比較する

bool BaseBullet::IsIntersectSea()const
{
	const float y = m_transform.m_position.y;

	if (y <= 0)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//弾とキャラクターとの当たり判定
//引数としてキャラクター座標をもらってくる

bool BaseBullet::IsHit(glm::vec3 _pos)const
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