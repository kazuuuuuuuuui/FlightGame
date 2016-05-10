#ifndef PARTICLE_H_
#define PARTICLE_H_

#include"Effect.h"

class Particle :public oka::Effect
{
public:
	float m_alpha;
	glm::vec3 m_color;
	glm::vec3 m_speed;

	void Draw();
	void Update();

	Particle(glm::vec3 _pos,glm::vec3 _color):
	m_alpha(1.0f)
	{
		m_transform.SetPosition(_pos);
		m_transform.SetScale(glm::vec3(0.0f, 0.0f, 0.0f));
		m_color = _color;
	}
};

#endif