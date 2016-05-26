#include<stdio.h>
#include"JoysticManager.h"

namespace oka
{
	JoysticManager* JoysticManager::m_instance = nullptr;

	//-------------------------------------------------------------------------------------------------------
	//�W���C�X�e�B�b�N�̃C���X�^���X�擾

	JoysticManager* JoysticManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new JoysticManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//�R���g���[�����Ǘ����Ă���x�N�^�[�ɓ����

	void JoysticManager::AddController(Contoroller *_controller)
	{
		m_contoroller.push_back(_controller);
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