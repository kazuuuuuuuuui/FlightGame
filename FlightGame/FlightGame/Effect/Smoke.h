#ifndef SMOKE_H_
#define SMOKE_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"
#include"Particle.h"

class Smoke;
typedef std::shared_ptr<Smoke> SmokeSP;

class Smoke :public oka::GameObject
{
public:
	std::list<ParticleSP>m_particles;
	static SmokeSP Create(glm::vec3 _basePos, unsigned int _particleNum, glm::vec3 _color);

	void Draw()override;
	void Update()override;

	Smoke(glm::vec3 _basePos, unsigned int _particleNum, glm::vec3 _color);
	~Smoke();
};

#endif