#include"CharacterManager.h"
#include"../../MyLibrary/Manager/GameManager.h"
#include"../../Character/Enemy.h"

namespace oka
{
	CharacterManager* CharacterManager::m_instance = nullptr;
	const unsigned int CharacterManager::m_maxEnemyNum = 10;//��x�ɏo������G�̐�

	//-------------------------------------
	//�R���X�g���N�^

	CharacterManager::CharacterManager():
		m_flame(0),
		m_player(nullptr)
	{

	}

	//-------------------------------------
	//�f�X�g���N�^
	//

	CharacterManager::~CharacterManager()
	{
		m_characters.clear();
	};

	//-------------------------------------
	//�X�V

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
	//�v���C���[���Q�Ƃ��邽�߂̃|�C���^��
	//

	void CharacterManager::SetPlayer(PlayerSP _player)
	{
		if (nullptr == m_player)
		{
			m_player = _player;
		}
	}

	//------------------
	//�L�����N�^�[�̒ǉ�

	void CharacterManager::AddCharacter(CharacterSP _character)
	{
		m_characters.push_back(_character);
	}

	//-------------------------------------
	//�v���C���[�̊�����Ԃ��m�F����

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
	//�L�����N�^�[�̊�����Ԃ��m�F����

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
	//�t���[����1�����̓G�̏o�����ɖ����Ȃ����
	//�ďo��������

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


