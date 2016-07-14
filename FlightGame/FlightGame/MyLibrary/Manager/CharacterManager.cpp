#include"CharacterManager.h"
#include"../../MyLibrary/Manager/GameManager.h"
#include"../../Character/Enemy.h"

namespace oka
{
	CharacterManager* CharacterManager::m_instance = nullptr;
	const unsigned int CharacterManager::m_maxEnemyNum = 10;//�t�B�[���h�Ɉ�x�ɏo������G�̐��̏��

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
			//Respawn();
		}
	}

	//-------------------------------------
	//�v���C���[���Q�Ƃ��邽�߂̃|�C���^��
	//���@���i�[����

	void CharacterManager::SetPlayer(PlayerSP _player)
	{
		m_player = _player;
	}

	//-------------------------------------
	//���@�ւ̃X�}�[�g�|�C���^��Ԃ�

	PlayerSP CharacterManager::GetPlayer()const
	{
		return m_player;
	}

	//------------------
	//�L�����N�^�[�̒ǉ�

	void CharacterManager::AddCharacter(CharacterSP _character)
	{
		m_characters.push_back(_character);
	}

	//-------------------------------------
	//�L�����N�^�[���i�[���ꂽlist�̃A�h���X��Ԃ�

	std::list<CharacterSP>* CharacterManager::GetCharacters()
	{
		return &m_characters;
	}

	//-------------------------------------
	//�v���C���[�̊�����Ԃ��m�F����

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
	//�L�����N�^�[�̊�����Ԃ��m�F����

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
	//����t���[����1�����̓G�̏o�����ɖ����Ȃ����
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


