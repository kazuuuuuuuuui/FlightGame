#include<stdio.h>
#include"JoysticManager.h"

namespace oka
{
	JoysticManager* JoysticManager::m_instance = nullptr;

	//-------------------------------------------------------------------------------------------------------
	//ジョイスティックのインスタンス取得

	JoysticManager* JoysticManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new JoysticManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//コントローラを管理しているベクターに入れる

	void JoysticManager::AddController(Contoroller *_controller)
	{
		m_contoroller.push_back(_controller);
	}

	
	//-------------------------------------
	//登録されているコントローラーの
	//接続状態をチェックする

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