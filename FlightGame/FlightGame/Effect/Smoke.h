#ifndef SMOKE_H_
#define SMOKE_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"
#include"Particle.h"
#include"EffectInfo.h"

class Smoke;
typedef std::shared_ptr<Smoke> SmokeSP;

class Smoke :public oka::GameObject
{
public:
	std::list<ParticleSP>m_particles;
	static SmokeSP Create(EffectInfo _info);

	void Draw();
	void Update();

	Smoke(EffectInfo _info);
};

#endif