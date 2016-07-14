#include"BulletManager.h"

namespace oka
{

	BulletManager* BulletManager::m_instance = nullptr;

	//-------------------------------------
	//

	BulletManager::BulletManager()
	{

	}

	//-------------------------------------
	//

	BulletManager::~BulletManager()
	{
		m_bullets.clear();
	}

	//--------------------------------------
	//弾マネージャー更新
	//常にオブジェクトの活性状態を判別する

	void BulletManager::Update()
	{
		CheckBullets();
	}

	//-------------------------------------
	//弾の追加

	void BulletManager::SetBullet(BaseBulletSP _bullet)
	{
		m_bullets.push_back(_bullet);
	}


	//--------------------------------------------
	//弾の活性状態のチェック

	void BulletManager::CheckBullets()
	{
		auto itr = m_bullets.begin();
		auto end = m_bullets.end();
		while (itr != end)
		{
			if (false == (*itr)->IsActive())
			{
				itr = m_bullets.erase(itr);
				continue;
			}

			itr++;
		}
	}

}