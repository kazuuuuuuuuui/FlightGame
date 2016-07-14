#include"BaseSingleton.h"

std::vector<BaseSingleton*> BaseSingleton::m_singletons;

//-------------------------------------
//コンストラクタ
//生成されたシングルトンクラス自身を
//ベクターに格納する

BaseSingleton::BaseSingleton()
{
	m_singletons.push_back(this);
}

//-------------------------------------
//ベクターに格納されたシングルトンクラスの更新を呼ぶ

void BaseSingleton::Update()
{
	for (unsigned int i = 0; i < m_singletons.size(); i++)
	{
		m_singletons[i]->Update();
	}
}

//-------------------------------------
//ベクターに格納されたシングルトンクラスを破棄する

void BaseSingleton::AllDestroy()
{
	for (unsigned int i = 0; i < m_singletons.size(); i++)
	{
		m_singletons[i]->Destroy();
	}
}

//-------------------------------------
//シングルトンクラスを格納するベクターを空にする

void BaseSingleton::Clear()
{
	m_singletons.clear();
}