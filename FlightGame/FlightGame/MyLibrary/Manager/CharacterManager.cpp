#include"CharacterManager.h"

namespace oka
{
	CharacterManager* CharacterManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^

	CharacterManager::CharacterManager()
	{
		printf("�L�����N�^�[�}�l�[�W���[����\n");
		printf("\n");

	}

	//-------------------------------------
	//�f�X�g���N�^
	//

	CharacterManager::~CharacterManager()
	{
		//debug
		printf("�L�����N�^�[�}�l�[�W���[�폜\n");
		printf("\n");

		m_characters.clear();

	};


	//-------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	CharacterManager* CharacterManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new CharacterManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//���g��nullptr�łȂ��ꍇ�������g��j������

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
		CheckCharacter();
	}

	//------------------
	//�L�����N�^�[�̒ǉ�

	void CharacterManager::AddCharacter(CharacterSP _character)
	{
		m_characters.push_back(_character);
	}

	//--------------------------------------------
	//

	void CharacterManager::CheckCharacter()
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


