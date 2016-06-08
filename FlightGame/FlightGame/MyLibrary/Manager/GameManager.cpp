#include"GameManager.h"

namespace oka
{
	GameManager* GameManager::m_instance = nullptr;

	//------------------------------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	GameManager* GameManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new GameManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//���g��nullptr�łȂ��ꍇ�������g��j������

	void GameManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}


	//--------------------------------------
	//�Q�[���̃}�l�[�W���[�X�V
	//��ɃI�u�W�F�N�g�̊�����Ԃ𔻕ʂ���

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
	//�Q�[���Ɍ����I�u�W�F�N�g�̒ǉ�

	void GameManager::Add(std::string _str,GameObjectSP _object)
	{
		m_gameObjects.insert(std::make_pair(_str, _object));
	}

	//-------------------------------------
	//map�ɓo�^����Ă���I�u�W�F�N�g��Ԃ�

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
	//�Q�[���Ɍ����I�u�W�F�N�g�̃���������ƍ폜
	//�񊈐��Ȃ�΃���������������X�g�[���珜�O����

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