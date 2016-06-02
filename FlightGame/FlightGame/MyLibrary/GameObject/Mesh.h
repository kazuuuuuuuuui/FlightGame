#ifndef OKA_MESH_H
#define OKA_MESH_H

#include"GameObject.h"
#include"../Model/Model.h"

namespace oka
{
	class Mesh;
	typedef std::shared_ptr<Mesh> MeshSP;

	class Mesh :public oka::GameObject
	{
	public:
		bool m_isLighting;
		bool m_isBlend;
		
		ModelSP m_model;
		unsigned int m_texture;

		static MeshSP Create(ModelSP _model, unsigned int _texture);
		void Draw();
		void Update() {};

		Mesh(ModelSP _model,unsigned int _texture);
		~Mesh() {};
	};
}
#endif