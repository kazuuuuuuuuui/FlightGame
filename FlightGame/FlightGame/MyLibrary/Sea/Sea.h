#ifndef OKA_SEA_H_
#define OKA_SEA_H_

#include"../GameObject/GameObject.h"
#include"../GameObject/Mesh.h"

namespace oka
{
	class Sea :public GameObject
	{
	public:
		Mesh *m_sea[3];

		void Draw();
		void Update();

		Sea();
	};
}

#endif