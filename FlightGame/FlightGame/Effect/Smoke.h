#ifndef SMOKE_H_
#define SMOKE_H_

#include<list>
#include"Effect.h"
#include"Particle.h"

class Smoke;
typedef std::shared_ptr<Smoke> SmokeSP;

class Smoke :public oka::Effect
{
public:
	std::list<ParticleSP>m_particles;
	static SmokeSP Create(glm::vec3 _pos,const unsigned int _particleNum);

	void Draw();
	void Update();

	Smoke(glm::vec3 _pos);
};

#endif