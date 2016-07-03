#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#include<stdio.h>
#include<string>
#include<list>
#include"../../Singleton/Singleton.h"
#include"../../Bullet/BaseBullet.h"

namespace oka
{
	class BulletManager :public Singleton<BulletManager>
	{
		friend class Singleton<BulletManager>;

	public:
		virtual void Update()override;
		void AddBullet(BaseBulletSP _bullet);
		void CheckBullets();

	private:
		static BulletManager* m_instance;
		std::list<BaseBulletSP>m_bullets;

		BulletManager();
		~BulletManager();
	};

}

#endif