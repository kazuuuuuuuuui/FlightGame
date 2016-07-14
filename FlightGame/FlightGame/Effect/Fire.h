#ifndef FIRE_H_
#define FIRE_H_

#include<list>
#include"Particle.h"

class Fire;
typedef std::shared_ptr<Fire> FireSP;

class Fire :public oka::GameObject
{
public:
	std::list<ParticleSP>m_particles;
	static FireSP Create(glm::vec3 _basePos,unsigned int _particleNum,glm::vec3 _color);

	void Draw()override;
	void Update()override;

	Fire(glm::vec3 _basePos, unsigned int _particleNum, glm::vec3 _color);
};

#endif