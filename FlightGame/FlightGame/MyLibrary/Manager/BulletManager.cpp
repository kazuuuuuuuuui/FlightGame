#include"BulletManager.h"

namespace oka
{

	BulletManager* BulletManager::m_instance = nullptr;

	//------------------------------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	BulletManager* BulletManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new BulletManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//���g��nullptr�łȂ��ꍇ�������g��j������

	void BulletManager::Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}


	//--------------------------------------
	//�e�}�l�[�W���[�X�V
	//��ɃI�u�W�F�N�g�̊�����Ԃ𔻕ʂ���

	void BulletManager::Updata()
	{
		CheckBullets();
	}

	//-------------------------------------
	//�e�̒ǉ�

	void BulletManager::AddBullet(Bullet* _bullet)
	{
		m_bullets.push_back(_bullet);
	}


	//--------------------------------------------
	//�e�̊�����Ԃ̃`�F�b�N

	void BulletManager::CheckBullets()
	{
		auto itr = m_bullets.begin();
		while (itr != m_bullets.end())
		{
			if ((*itr)->CheckIsActive())
			{

			}
			else
			{
				//delete itr->second;
				itr = m_bullets.erase(itr);
				continue;
			}

			itr++;

		}
	}

}