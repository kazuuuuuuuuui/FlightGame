#include"Sky.h"
#include"../Manager/GameManager.h"
#include"../Manager/ModelManager.h"
#include"../Manager/ImageManager.h"
#include"../Math/MyMath.h"
#include"../../glut.h"

namespace oka
{
	Sky::Sky()
	{
		Model *sky = oka::ModelManager::GetInstance()->m_models["Sky"];
		unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("Sky"));
		m_sky = new oka::Mesh(sky, tex);

		//位置と向きとスケール調整
		m_sky->m_isLighting = false;
		const glm::vec3 pos = glm::vec3(128.0f, 0.0f, -128.0f);
		m_sky->m_transform.m_position = pos;
		const float angle = MyMath::ToRadian(90.0f);
		const glm::vec3 axis = glm::vec3(1, 0, 0);
		m_sky->m_transform.m_rotate = MyMath::Rotate(angle, axis);
		
		m_sky->m_transform.m_scale = glm::vec3(300.0f, 300.0f, 300.0f);
		GameManager::GetInstance()->AddGameObject("Sky", m_sky);
	}
}