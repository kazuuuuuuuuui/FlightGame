#ifndef OKA_SKY_H_
#define OKA_SKY_H_

#include"../GameObject/GameObject.h"
#include"../GameObject/Mesh.h"

namespace oka
{
	class Sky;
	typedef std::shared_ptr<Sky> SkySP;

	class Sky :public GameObject
	{
	public:
		MeshSP m_sky;

		static SkySP Create();
		void Draw() {};
		void Update() {};

		Sky();
	};
}

#endif