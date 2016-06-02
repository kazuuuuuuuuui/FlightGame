#include"FealdManager.h"

namespace oka
{
	FealdManager* FealdManager::m_instance = nullptr;

	//-------------------------------------
	//�f�X�g���N�^
	//

	FealdManager::~FealdManager()
	{

	};


	//-------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	FealdManager* FealdManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new FealdManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//���g��nullptr�łȂ��ꍇ�������g��j������

	void FealdManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}


	//------------------
	//�t�B�[���h�̒ǉ�

	void FealdManager::AddFeald(FealdSP _feald)
	{
		if (nullptr == m_feald)
		{
			m_feald = _feald;
		}
	}

}


