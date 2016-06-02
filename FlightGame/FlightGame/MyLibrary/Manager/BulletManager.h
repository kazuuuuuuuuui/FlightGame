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
			printf("弾マネージャーが生成されました\n");
			printf("\n");

		}

		~BulletManager()
		{
			//debug
			printf("弾マネージャーが削除されました\n");
			printf("\n");
		}



	};

}

#endif