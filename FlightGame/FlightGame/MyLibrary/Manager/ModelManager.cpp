#include"ModelManager.h"

namespace oka
{
	ModelManager* ModelManager::m_instance = nullptr;

	//-------------------------------------
	//�Q�[���Ɍ���郂�f���f�[�^�̒ǉ�
	//key�̂��̂����ɓo�^����Ă��邩������
	//�Ȃ���ΊǗ����Ă���}�b�v�ɒǉ�����

	void ModelManager::SetModel(std::string _str, ModelSP _model)
	{
		if (m_models.find(_str) == m_models.end())
		{
			m_models.insert(std::make_pair(_str, _model));
		}
	}

	//-------------------------------------
	//���f���f�[�^�̎擾
	//�����Ƃ���string�^�̕�������󂯎��
	//Model�N���X�̃X�}�[�g�|�C���^��Ԃ�

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