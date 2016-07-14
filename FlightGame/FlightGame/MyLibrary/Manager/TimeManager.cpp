#include<stdio.h>
#include"TimeManager.h"
#include"CharacterManager.h"

namespace oka
{
	TimeManager* TimeManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^

	TimeManager::TimeManager()
	{
		//�Q�[���̐�������
		m_gameTime = 60;

		m_flame = 60 * m_gameTime;
	}

	//------------------------
	//�X�V
	//����̃t���[�����f�N�������g����
	//�t���[��������~���b�E�b�E�����Z�o����

	void TimeManager::Update()
	{
		if (nullptr != oka::CharacterManager::GetInstance()->GetPlayer())
		{
			const bool isHit = oka::CharacterManager::GetInstance()->GetPlayer()->GetIsHitAttack();
			if (isHit)
			{
				MinusTime();
			}
		}

		if (m_flame > 0)
		{
			m_flame--;
		}
		else
		{
			m_flame = 0;
		}

		m_milliSecond = ((m_flame * 1000) / 60) % 1000;
		m_second = m_flame / 60;
		m_minute = m_second / 60;
	}

	//-------------------------------------
	//�t���[�����擾����

	unsigned int TimeManager::GetFlame()const
	{
		return m_flame;
	}

	//-------------------------------------
	//�~���b���擾����

	unsigned int TimeManager::GetMilliSecond()const
	{
		return m_milliSecond;
	}

	//-------------------------------------
	//�b���擾����

	unsigned int TimeManager::GetSecond()const
	{
		return m_second % 60;
	}

	//-------------------------------------
	//�����擾����

	unsigned int TimeManager::GetMinutes()const
	{
		return m_minute;
	}

	//-------------------------------------
	//�v���C���[���U�����󂯂��ۂ�
	//�c�莞�Ԃ����Z����

	void TimeManager::MinusTime()
	{
		const unsigned int minusValue = 1;
		m_flame -= minusValue;
	}

}//namespace oka