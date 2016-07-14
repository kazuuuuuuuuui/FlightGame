#include"CharacterManager.h"
#include"../../MyLibrary/Manager/GameManager.h"
#include"../../Character/Enemy.h"

namespace oka
{
	CharacterManager* CharacterManager::m_instance = nullptr;
	const unsigned int CharacterManager::m_maxEnemyNum = 10;//フィールドに一度に出現する敵の数の上限

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
			//Respawn();
		}
	}

	//-------------------------------------
	//プレイヤーを参照するためのポインタに
	//自機を格納する

	void CharacterManager::SetPlayer(PlayerSP _player)
	{
		m_player = _player;
	}

	//-------------------------------------
	//自機へのスマートポインタを返す

	PlayerSP CharacterManager::GetPlayer()const
	{
		return m_player;
	}

	//------------------
	//キャラクターの追加

	void CharacterManager::AddCharacter(CharacterSP _character)
	{
		m_characters.push_back(_character);
	}

	//-------------------------------------
	//キャラクターが格納されたlistのアドレスを返す

	std::list<CharacterSP>* CharacterManager::GetCharacters()
	{
		return &m_characters;
	}

	//-------------------------------------
	//プレイヤーの活性状態を確認する

	void CharacterManager::CheckPlayer()
	{
		if (nullptr != m_player)
		{
			if (false == m_player->IsActive())
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
			if (false == (*itr)->m_isActive)
			{
				itr = m_characters.erase(itr);
				continue;
			}

			itr++;

		}
	}

	//-------------------------------------
	//既定フレームに1回既定の敵の出現数に満たなければ
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


