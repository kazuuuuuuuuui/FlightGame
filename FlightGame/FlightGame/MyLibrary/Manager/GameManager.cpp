#include"GameManager.h"

namespace oka
{
	GameManager* GameManager::m_instance = nullptr;

	//------------------------------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	GameManager* GameManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new GameManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//自身がnullptrでない場合自分自身を破棄する

	void GameManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}


	//--------------------------------------
	//ゲームのマネージャー更新
	//常にオブジェクトの活性状態を判別する

	void GameManager::Updata()
	{
		auto itr = m_gameObjects.begin();
		while (itr != (m_gameObjects.end()))
		{
			itr->second->m_transform.Update();

			itr++;
		}
		
		CheckGameObject();
	}

	//-------------------------------------
	//ゲームに現れるオブジェクトの追加

	void GameManager::Add(std::string _str,GameObjectSP _object)
	{
		m_gameObjects.insert(std::make_pair(_str, _object));
	}

	//-------------------------------------
	//mapに登録されているオブジェクトを返す

	/*GameObjectSP GameManager::GetObject(std::string _str)
	{
		if (m_images.find(_str) == m_images.end())
		{
			m_images.insert(std::make_pair(_str, _handle));
		}
		else
		{
			assert()
		}	
	}*/

	//--------------------------------------------
	//ゲームに現れるオブジェクトのメモリ解放と削除
	//非活性ならばメモリを解放しリストーから除外する

	void GameManager::CheckGameObject()
	{
		auto itr = m_gameObjects.begin();
		auto end = m_gameObjects.end();
		while (itr != end)
		{
			if (itr->second->IsActive())
			{

			}
			else
			{
				itr = m_gameObjects.erase(itr);
				continue;
			}

			itr++;

		}
	}
}