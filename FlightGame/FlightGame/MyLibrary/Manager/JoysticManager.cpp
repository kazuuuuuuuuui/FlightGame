#include<stdio.h>
#include"JoysticManager.h"

namespace oka
{
	JoysticManager* JoysticManager::m_instance = nullptr;

	//-------------------------------------
	//コンストラクタ

	JoysticManager::JoysticManager()
	{

	}

	//-------------------------------------
	//デストラクタ

	JoysticManager::~JoysticManager()
	{
		m_contoroller.clear();
	}

	////-------------------------------------------------------------------------------------------------------
	////ジョイスティックのインスタンス取得

	//JoysticManager* JoysticManager::GetInstance()
	//{
	//	if (nullptr == m_instance)
	//	{
	//		m_instance = new JoysticManager();
	//	}

	//	return m_instance;
	//}

	////-------------------------------------
	////自身がnullptrでない場合自分自身を破棄する

	//void JoysticManager::Destroy()
	//{
	//	if (m_instance)
	//	{
	//		delete m_instance;
	//		m_instance = nullptr;
	//	}
	//}


	//-------------------------------------
	//コントローラを管理しているベクターに入れる

	void JoysticManager::SetController(Contoroller *_controller)
	{
		m_contoroller.push_back(_controller);
	}

	//-------------------------------------
	//引数として受け取った数番目の
	//コントローラーへのポインタを返す
	//参照先がnullptrならばassert

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