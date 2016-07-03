#include"BulletManager.h"

namespace oka
{

	BulletManager* BulletManager::m_instance = nullptr;

	//-------------------------------------
	//

	BulletManager::BulletManager()
	{

	}

	//-------------------------------------
	//

	BulletManager::~BulletManager()
	{
		m_bullets.clear();
	}

	//--------------------------------------
	//�e�}�l�[�W���[�X�V
	//��ɃI�u�W�F�N�g�̊�����Ԃ𔻕ʂ���

	void BulletManager::Update()
	{
		CheckBullets();
	}

	//-------------------------------------
	//�e�̒ǉ�

	void BulletManager::AddBullet(BaseBulletSP _bullet)
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
			if ((*itr)->IsActive())
			{

			}
			else
			{
				itr = m_bullets.erase(itr);
				continue;
			}

			itr++;

		}
	}

}