#ifndef FIRE_H_
#define FIRE_H_

#include<list>
#include"Effect.h"
#include"Particle.h"

class Fire;
typedef std::shared_ptr<Fire> FireSP;

class Fire :public oka::Effect
{
public:
	static const int m_particleNum;
	std::list<ParticleSP>m_particles;

	static FireSP Create(glm::vec3 _pos);

	void Draw();
	void Update();

	Fire(glm::vec3 _pos);
};

#endif