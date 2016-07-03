#include"CharacterManager.h"
#include"../../MyLibrary/Manager/GameManager.h"
#include"../../Character/Enemy.h"

namespace oka
{
	CharacterManager* CharacterManager::m_instance = nullptr;
	const unsigned int CharacterManager::m_maxEnemyNum = 10;//一度に出現する敵の数

	//-------------------------------------
	//コンストラクタ

	CharacterManager::CharacterManager():
		m_flame(0),
		m_player(nullptr)
	{

	}

	//-------------------------------------
	//デストラクタ
	//

	CharacterManager::~CharacterManager()
	{
		m_characters.clear();
	};

	//-------------------------------------
	//更新

	void CharacterManager::Update()
	{
		m_flame++;

		CheckPlayer();
		CheckCharacters();

		if (0 == m_flame % (60 * 3))
		{
			Respawn();
		}
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
	//プレイヤーの活性状態を確認する

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
	//キャラクターの活性状態を確認する

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

	//-------------------------------------
	//フレームに1回既定の敵の出現数に満たなければ
	//再出現させる

	void CharacterManager::Respawn()
	{
		const unsigned int enemyNum = m_characters.size() + 1;

		if (enemyNum < m_maxEnemyNum)
		{
			EnemySP enemy = Enemy::Create();
			m_characters.push_back(enemy);
			oka::GameManager::GetInstance()->Add("Enemy", enemy);
		}
	}

}


