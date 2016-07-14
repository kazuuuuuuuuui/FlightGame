#include"ModelManager.h"

namespace oka
{
	ModelManager* ModelManager::m_instance = nullptr;

	//-------------------------------------
	//ゲームに現れるモデルデータの追加
	//keyのものが既に登録されているか検索し
	//なければ管理しているマップに追加する

	void ModelManager::SetModel(std::string _str, ModelSP _model)
	{
		if (m_models.find(_str) == m_models.end())
		{
			m_models.insert(std::make_pair(_str, _model));
		}
	}

	//-------------------------------------
	//モデルデータの取得
	//引数としてstring型の文字列を受け取り
	//Modelクラスのスマートポインタを返す

	ModelSP ModelManager::GetModel(std::string _str)const
	{
		if (m_models.find(_str) == m_models.end())
		{
			assert(0);
			return nullptr;
		}
		else
		{
			return m_models.find(_str)->second;
		}
	}
}