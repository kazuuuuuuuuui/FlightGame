#ifndef FIRE_H_
#define FIRE_H_

#include<list>
#include"EffectInfo.h"
#include"Particle.h"

class Fire;
typedef std::shared_ptr<Fire> FireSP;

class Fire :public oka::GameObject
{
public:
	std::list<ParticleSP>m_particles;
	static FireSP Create(EffectInfo _info);

	void Draw();
	void Update();

	Fire(EffectInfo _info);
};

#endif