#ifndef OKA_MESH_H
#define OKA_MESH_H

#include"GameObject.h"
#include"../Model/Model.h"

namespace oka
{
	class Mesh :public oka::GameObject
	{
	public:
		bool m_isLighting;
		bool m_isBlend;
		
		Model *m_model;
		unsigned int m_texture;

		void Draw();
		void Update() {};

		Mesh(Model *_model,unsigned int _texture);
		~Mesh() {};
	};
}
#endif