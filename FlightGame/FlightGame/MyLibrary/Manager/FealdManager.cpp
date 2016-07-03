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

	//-------------------------------------
	//参照しているフィールドの横幅を返す

	const int FealdManager::GetFealdWidth()const
	{
		return m_feald->m_width;
	}

	//-------------------------------------
	//参照しているフィールドの縦幅を返す

	const int FealdManager::GetFealdDepth()const
	{
		return m_feald->m_height;
	}

}


