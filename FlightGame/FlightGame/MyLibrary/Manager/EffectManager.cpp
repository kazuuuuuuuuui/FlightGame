#include"EffectManager.h"

namespace oka
{

	EffectManager* EffectManager::m_instance = nullptr;

	//-------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	EffectManager* EffectManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new EffectManager();
		}

		return m_instance;
	}

	//-------------------------------------
	//�Ǘ����Ă��郊�X�g�ɒǉ�����

	void EffectManager::AddEffects(oka::Effect* _effect)
	{
		m_effects.push_back(_effect);
	}


	//-------------------------------------
	//������Ԃ𒲂ׂĔ񊈐��Ȃ�
	//�Ǘ����Ă��郊�X�g����폜

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