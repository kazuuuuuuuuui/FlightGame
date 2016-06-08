#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#include<stdio.h>
#include<string>
#include<list>
#include"../../Bullet/BaseBullet.h"

namespace oka
{

	class BulletManager
	{
	public:
		std::list<BaseBulletSP>m_bullets;

		void Updata();
		void AddBullet(BaseBulletSP _bullet);
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