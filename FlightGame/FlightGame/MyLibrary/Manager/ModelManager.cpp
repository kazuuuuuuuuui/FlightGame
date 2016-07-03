#include"ModelManager.h"

namespace oka
{
	ModelManager* ModelManager::m_instance = nullptr;

	//-------------------------------------
	//ゲームに現れるモデルデータの追加
	//keyのものが既に登録されているか検索し
	//なければ管理しているマップに追加する

	void ModelManager::Add(std::string _str, ModelSP _model)
	{
		if (m_models.find(_str) == m_models.end())
		{
			m_models.insert(std::make_pair(_str, _model));
		}
	}


}