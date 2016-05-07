#ifndef SMOKE_H_
#define SMOKE_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"
#include"Particle.h"

class Smoke :public oka::GameObject
{
public:
	static const int m_particleNum;
	std::list<Particle*>m_particles;

	static Smoke* Create(glm::vec3 _pos);

	void Draw();
	void Update();

	Smoke(glm::vec3 _pos);
};

#endif