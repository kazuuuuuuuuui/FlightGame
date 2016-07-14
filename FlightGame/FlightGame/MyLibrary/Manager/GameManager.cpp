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
	//�f�X�g���N�^

	GameManager::~GameManager()
	{
		m_gameObjects.clear();
	}

	//--------------------------------------
	//�Q�[���̃}�l�[�W���[�X�V
	//��ɃI�u�W�F�N�g�̊�����Ԃ𔻕ʂ���

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