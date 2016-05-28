#include"Sea.h"
#include"../Math/MyMath.h"
#include"../Manager/GameManager.h"
#include"../Manager/ModelManager.h"
#include"../Manager/ImageManager.h"
#include"../../glut.h"

namespace oka
{
	Sea::Sea()
	{
		Model *sea = oka::ModelManager::GetInstance()->m_models["Sea"];
		unsigned int tex = (oka::ImageManager::GetInstance()->GetHandle("Sea"));

		for (int i = 0; i < 3; i++)
		{
			m_sea[i] = new oka::Mesh(sea, tex);

			//位置と向きとスケール調整
			m_sea[i]->m_isBlend = true;

			const glm::vec3 pos = glm::vec3(128.0f, i*0.5f, -128.0f);
			m_sea[i]->m_transform.m_position = pos;
			const float angle = MyMath::ToRadian(90.0f);
			const glm::vec3 axis = glm::vec3(1, 0, 0);
			m_sea[i]->m_transform.m_rotate = MyMath::Rotate(angle, axis);

			m_sea[i]->m_transform.m_scale = glm::vec3(500.0f, 500.0f, 500.0f);
			GameManager::GetInstance()->AddGameObject("Sea", m_sea[i]);
		}
	}


	void Sea::Update()
	{
			static float angle = 0.0f;
			angle += oka::MyMath::ToRadian(1.0f);

			const float mv = sinf(angle)*0.1f;

			m_sea[0]->m_transform.m_position.x += mv;
			m_sea[1]->m_transform.m_position.x -= mv;
			m_sea[2]->m_transform.m_position.x += (mv / 2);
	}

	void Sea::Draw()
	{}
}