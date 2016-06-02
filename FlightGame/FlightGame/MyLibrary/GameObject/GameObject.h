#ifndef _OKA_GAMEOBJECT_H_
#define _OKA_GAMEOBJECT_H_

#include<memory>
#include"Transform.h"
#include"../../glm/vec2.hpp"

//-------------------------------

namespace oka
{
	//GameObjectへのスマートポインタを定義化
	class GameObject;
	typedef std::shared_ptr<GameObject> GameObjectSP;

	class GameObject 
	{
	public:
		//自身のフレーム
		unsigned int m_flame;

		//活性か非活性かのフラグ
		bool m_isActive;

		//自身の位置・回転・拡大縮小情報
		Transform m_transform;

		virtual void Draw() {};
		virtual void Update();
		bool IsActive()const;

		GameObject() :
			m_flame(0),
			m_isActive(true)
		{};

		virtual ~GameObject() {};
	};

}

#endif