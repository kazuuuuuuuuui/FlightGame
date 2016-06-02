#ifndef OKA_SEA_H_
#define OKA_SEA_H_

#include"../GameObject/GameObject.h"
#include"../GameObject/Mesh.h"

namespace oka
{
	class Sea;
	typedef std::shared_ptr<Sea> SeaSP;

	class Sea :public GameObject
	{
	public:
		MeshSP m_sea[3];

		static SeaSP Create();
		void Draw();
		void Update();

		Sea();
	};
}

#endif