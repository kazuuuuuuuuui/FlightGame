#include"CharacterManager.h"

namespace oka
{
	CharacterManager* CharacterManager::m_instance = nullptr;

	//-------------------------------------
	//コンストラクタ

	CharacterManager::CharacterManager():
		m_player(nullptr)
	{
		printf("キャラクターマネージャー生成\n");
		printf("\n");

	}

	//-------------------------------------
	//デストラクタ
	//

	CharacterManager::~CharacterManager()
	{
		//debug
		printf("キャラクターマネージャー削除\n");
		printf("\n");

		m_characters.clear();

	};


	//-------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	CharacterManager* CharacterManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new CharacterManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//自身がnullptrでない場合自分自身を破棄する

	void CharacterManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	void CharacterManager::Update()
	{
		CheckPlayer();
		CheckCharacters();
	}

	//-------------------------------------
	//プレイヤーを参照するためのポインタに
	//

	void CharacterManager::SetPlayer(PlayerSP _player)
	{
		if (nullptr == m_player)
		{
			m_player = _player;
		}
	}

	//------------------
	//キャラクターの追加

	void CharacterManager::AddCharacter(CharacterSP _character)
	{
		m_characters.push_back(_character);
	}

	//-------------------------------------
	//

	void CharacterManager::CheckPlayer()
	{
		if (nullptr != m_player)
		{
			if (m_player->IsActive())
			{

			}
			else
			{
				m_player = nullptr;
			}
		}
	}

	//--------------------------------------------
	//

	void CharacterManager::CheckCharacters()
	{
		auto itr = m_characters.begin();
		while (itr != m_characters.end())
		{
			if ((*itr)->m_isActive)
			{

			}
			else
			{
				itr = m_characters.erase(itr);
				continue;
			}

			itr++;

		}
	}

}


