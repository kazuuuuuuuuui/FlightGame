#ifndef OKA_EFFECT_H_
#define OKA_EFFECT_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"

namespace oka
{
	class Effect :public GameObject
	{
	public:

		virtual void Draw() = 0;
		virtual void Update() = 0;

		Effect() {};
	};

}

#endif