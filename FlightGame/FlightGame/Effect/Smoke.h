#ifndef SMOKE_H_
#define SMOKE_H_

#include<list>
#include"Effect.h"
#include"Particle.h"

class Smoke :public oka::Effect
{
public:
	std::list<Particle*>m_particles;
	static Smoke* Create(glm::vec3 _pos,const unsigned int _particleNum);

	void Draw();
	void Update();

	Smoke(glm::vec3 _pos);
};

#endif