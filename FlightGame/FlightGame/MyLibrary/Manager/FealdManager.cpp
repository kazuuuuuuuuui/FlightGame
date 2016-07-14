#include"FealdManager.h"

namespace oka
{
	FealdManager* FealdManager::m_instance = nullptr;

	//-------------------------------------
	//

	FealdManager::FealdManager() :
		m_feald(nullptr)
	{
	
	}


	//-------------------------------------
	//デストラクタ

	FealdManager::~FealdManager()
	{
		m_feald = nullptr;
	};


	//-------------------------------------
	//フィールドの追加

	void FealdManager::AddFeald(FealdSP _feald)
	{
		if (nullptr == m_feald)
		{
			m_feald = _feald;
		}
	}
}


