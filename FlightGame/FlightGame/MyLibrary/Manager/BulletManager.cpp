#include"BulletManager.h"

namespace oka
{

	BulletManager* BulletManager::m_instance = nullptr;

	//------------------------------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	BulletManager* BulletManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new BulletManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//自身がnullptrでない場合自分自身を破棄する

	void BulletManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}


	//--------------------------------------
	//弾マネージャー更新
	//常にオブジェクトの活性状態を判別する

	void BulletManager::Updata()
	{
		CheckBullets();
	}

	//-------------------------------------
	//弾の追加

	void BulletManager::AddBullet(Bullet* _bullet)
	{
		m_bullets.push_back(_bullet);
	}


	//--------------------------------------------
	//弾の活性状態のチェック

	void BulletManager::CheckBullets()
	{
		auto itr = m_bullets.begin();
		while (itr != m_bullets.end())
		{
			if ((*itr)->CheckIsActive())
			{

			}
			else
			{
				//delete itr->second;
				itr = m_bullets.erase(itr);
				continue;
			}

			itr++;

		}
	}

}