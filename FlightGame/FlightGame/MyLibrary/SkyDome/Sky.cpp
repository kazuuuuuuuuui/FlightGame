#include"Sky.h"
#include"../Manager/GameManager.h"
#include"../Manager/ModelManager.h"
#include"../Manager/ImageManager.h"
#include"../Math/MyMath.h"
#include"../../glut.h"

namespace oka
{
	//-------------------------------------
	//コンストラクタ

	Sky::Sky()
	{
		ModelSP sky = oka::ModelManager::GetInstance()->m_models["Sky"];
		unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("Sky"));
		m_sky = oka::Mesh::Create(sky, tex);

		//位置と向きとスケール調整
		m_sky->m_isLighting = false;
		const glm::vec3 pos = glm::vec3(128.0f, 0.0f, -128.0f);
		m_sky->m_transform.m_position = pos;
		const float angle = MyMath::ToRadian(90.0f);
		const glm::vec3 axis = glm::vec3(1, 0, 0);
		m_sky->m_transform.m_rotate = MyMath::Rotate(angle, axis);
		m_sky->m_transform.m_scale = glm::vec3(500.0f, 500.0f, 500.0f);
		GameManager::GetInstance()->Add("Sky", m_sky);
	}

	//-------------------------------------
	//生成

	SkySP Sky::Create()
	{
		SkySP sky(new Sky());

		return sky;
	}

	//-------------------------------------
	//更新

	void Sky::Update()
	{
		float angle = oka::MyMath::ToRadian(0.01f);
		glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);

		glm::tquat<float>quat = oka::MyMath::Rotate(angle, axis);

		m_sky->m_transform.m_rotate *= quat;
	}
}