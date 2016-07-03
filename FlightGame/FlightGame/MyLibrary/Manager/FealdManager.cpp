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
	//�f�X�g���N�^

	FealdManager::~FealdManager()
	{
		m_feald = nullptr;
	};


	//-------------------------------------
	//�t�B�[���h�̒ǉ�

	void FealdManager::AddFeald(FealdSP _feald)
	{
		if (nullptr == m_feald)
		{
			m_feald = _feald;
		}
	}

	//-------------------------------------
	//�Q�Ƃ��Ă���t�B�[���h�̉�����Ԃ�

	const int FealdManager::GetFealdWidth()const
	{
		return m_feald->m_width;
	}

	//-------------------------------------
	//�Q�Ƃ��Ă���t�B�[���h�̏c����Ԃ�

	const int FealdManager::GetFealdDepth()const
	{
		return m_feald->m_height;
	}

}


