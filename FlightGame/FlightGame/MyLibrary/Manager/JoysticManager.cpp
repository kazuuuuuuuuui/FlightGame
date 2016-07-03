#include<stdio.h>
#include"JoysticManager.h"

namespace oka
{
	JoysticManager* JoysticManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^

	JoysticManager::JoysticManager()
	{

	}

	//-------------------------------------
	//�f�X�g���N�^

	JoysticManager::~JoysticManager()
	{
		m_contoroller.clear();
	}

	////-------------------------------------------------------------------------------------------------------
	////�W���C�X�e�B�b�N�̃C���X�^���X�擾

	//JoysticManager* JoysticManager::GetInstance()
	//{
	//	if (nullptr == m_instance)
	//	{
	//		m_instance = new JoysticManager();
	//	}

	//	return m_instance;
	//}

	////-------------------------------------
	////���g��nullptr�łȂ��ꍇ�������g��j������

	//void JoysticManager::Destroy()
	//{
	//	if (m_instance)
	//	{
	//		delete m_instance;
	//		m_instance = nullptr;
	//	}
	//}


	//-------------------------------------
	//�R���g���[�����Ǘ����Ă���x�N�^�[�ɓ����

	void JoysticManager::SetController(Contoroller *_controller)
	{
		m_contoroller.push_back(_controller);
	}

	//-------------------------------------
	//�����Ƃ��Ď󂯎�������Ԗڂ�
	//�R���g���[���[�ւ̃|�C���^��Ԃ�
	//�Q�Ɛ悪nullptr�Ȃ��assert

	Contoroller* JoysticManager::GetController(unsigned int _num)const
	{
		if (nullptr == m_contoroller[_num])
		{
			return nullptr;
		}
		else
		{
			return m_contoroller[_num];
		}
	}

	
	//-------------------------------------
	//�o�^����Ă���R���g���[���[��
	//�ڑ���Ԃ��`�F�b�N����

	void JoysticManager::Update()
	{
		for (unsigned int i = 0; i < m_contoroller.size(); i++)
		{
			if (ERROR_SUCCESS == XInputGetState(i, &m_contoroller[i]->m_state))
			{
				m_contoroller[i]->m_isConnected = true;
				m_contoroller[i]->Update();
			}
			else
			{
				m_contoroller[i]->m_isConnected = false;
			}

		}

	}
}