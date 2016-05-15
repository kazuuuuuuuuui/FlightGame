#include"EffectManager.h"

namespace oka
{

	EffectManager* EffectManager::m_instance = nullptr;

	//-------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	EffectManager* EffectManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new EffectManager();
		}

		return m_instance;
	}

	//-------------------------------------
	//管理しているリストに追加する

	void EffectManager::AddEffects(oka::Effect* _effect)
	{
		m_effects.push_back(_effect);
	}


	//-------------------------------------
	//活性状態を調べて非活性なら
	//管理しているリストから削除

	void EffectManager::EraseEffect()
	{
		auto itr = m_effects.begin();
		while (itr != m_effects.end())
		{
			if ((*itr)->m_isActive)
			{

			}
			else
			{
				delete (*itr);
				itr = m_effects.erase(itr);
				continue;
			}

			itr++;

		}
	}

}