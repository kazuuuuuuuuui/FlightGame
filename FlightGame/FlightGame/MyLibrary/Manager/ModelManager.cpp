#include"ModelManager.h"

namespace oka
{
	ModelManager* ModelManager::m_instance = nullptr;

	//------------------------------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	ModelManager* ModelManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new ModelManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//���g��nullptr�łȂ��ꍇ�������g��j������

	void ModelManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	//-------------------------------------
	//�Q�[���Ɍ���郂�f���f�[�^�̒ǉ�
	//key�̂��̂����ɓo�^����Ă��邩������
	//�Ȃ���ΊǗ����Ă���}�b�v�ɒǉ�����

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