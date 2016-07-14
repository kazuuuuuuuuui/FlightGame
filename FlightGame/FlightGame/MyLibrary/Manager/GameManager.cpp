#include"GameManager.h"

namespace oka
{
	GameManager* GameManager::m_instance = nullptr;

	//-------------------------------------
	//

	GameManager::GameManager()
	{

	}

	//-------------------------------------
	//デストラクタ

	GameManager::~GameManager()
	{
		m_gameObjects.clear();
	}

	//--------------------------------------
	//ゲームのマネージャー更新
	//常にオブジェクトの活性状態を判別する

	void GameManager::Update()
	{	
		auto itr = m_gameObjects.begin();
		auto end = m_gameObjects.end();

		while (itr != end)
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
			const bool isActive = itr->second->IsActive();

			if (false == isActive)
			{
				itr = m_gameObjects.erase(itr);
				continue;
			}

			itr++;
		}
	}
}