#ifndef _OKA_GAMEOBJECT_H_
#define _OKA_GAMEOBJECT_H_

#include<vector>
#include"Transform.h"
#include"../../glm/vec2.hpp"

//-------------------------------

namespace oka
{
	class GameObject 
	{
	public:
		//自身のフレーム
		unsigned int m_flame;

		//活性か非活性かのフラグ
		bool m_isActive;

		//自身の位置・回転・拡大縮小情報
		Transform m_transform;

		bool CheckIsActive()const;

		GameObject() :
			m_flame(0),
			m_isActive(true)
		{};

		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}

#endif