#include"FealdManager.h"

namespace oka
{
	FealdManager* FealdManager::m_instance = nullptr;

	//-------------------------------------
	//デストラクタ
	//

	FealdManager::~FealdManager()
	{

	};


	//-------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	FealdManager* FealdManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new FealdManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//自身がnullptrでない場合自分自身を破棄する

	void FealdManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}


	//------------------
	//フィールドの追加

	void FealdManager::AddFeald(FealdSP _feald)
	{
		if (nullptr == m_feald)
		{
			m_feald = _feald;
		}
	}

}


