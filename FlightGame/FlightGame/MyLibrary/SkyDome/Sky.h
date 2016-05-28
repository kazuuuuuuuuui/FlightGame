#ifndef OKA_SKY_H_
#define OKA_SKY_H_

#include"../GameObject/GameObject.h"
#include"../GameObject/Mesh.h"

namespace oka
{

	class Sky :public GameObject
	{
	public:
		Mesh *m_sky;

		void Draw() {};
		void Update() {};

		Sky();
	};
}

#endif