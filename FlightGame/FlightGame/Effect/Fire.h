#ifndef FIRE_H_
#define FIRE_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"
#include"Particle.h"

class Fire :public oka::GameObject
{
public:
	static const int m_particleNum;
	std::list<Particle*>m_particles;

	static Fire* Create(glm::vec3 _pos);

	void Draw();
	void Update();

	Fire(glm::vec3 _pos);
};

#endif