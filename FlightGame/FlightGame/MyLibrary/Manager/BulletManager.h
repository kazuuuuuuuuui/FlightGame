#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#include<stdio.h>
#include<string>
#include<list>
#include"../../Bullet/Bullet.h"

namespace oka
{

	class BulletManager
	{
	public:
		std::list<BulletSP>m_bullets;

		void Updata();
		void Add(BulletSP _bullet);
		void CheckBullets();

		static BulletManager* GetInstance();
		static void Destroy();

	private:
		static BulletManager* m_instance;

		BulletManager()
		{
			//debug
			printf("�e�}�l�[�W���[����������܂���\n");
			printf("\n");

		}

		~BulletManager()
		{
			//debug
			printf("�e�}�l�[�W���[���폜����܂���\n");
			printf("\n");
		}



	};

}

#endif