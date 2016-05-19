#include"ModelManager.h"

namespace oka
{
	ModelManager* ModelManager::m_instance = nullptr;

	//------------------------------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	ModelManager* ModelManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new ModelManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//自身がnullptrでない場合自分自身を破棄する

	void ModelManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	//-------------------------------------
	//ゲームに現れるモデルデータの追加
	//keyのものが既に登録されているか検索し
	//なければ管理しているマップに追加する

	void ModelManager::AddModel(std::string _str, Model *_model)
	{
		if (m_models.find(_str) == m_models.end())
		{
			m_models.insert(std::make_pair(_str, _model));
		}
		else
		{

		}
	}


}