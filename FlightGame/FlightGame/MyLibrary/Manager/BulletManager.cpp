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

	void BulletManager::SetBullet(BaseBulletSP _bullet)
	{
		m_bullets.push_back(_bullet);
	}


	//--------------------------------------------
	//�e�̊�����Ԃ̃`�F�b�N

	void BulletManager::CheckBullets()
	{
		auto itr = m_bullets.begin();
		auto end = m_bullets.end();
		while (itr != end)
		{
			if (false == (*itr)->IsActive())
			{
				itr = m_bullets.erase(itr);
				continue;
			}

			itr++;
		}
	}

}