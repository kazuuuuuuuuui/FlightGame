#ifndef PARTICLE_H_
#define PARTICLE_H_

#include"../MyLibrary/GameObject/GameObject.h"

class Particle;
typedef std::shared_ptr<Particle> ParticleSP;

class Particle :public oka::GameObject
{
public:
	float m_alpha;
	glm::vec3 m_color;
	glm::vec3 m_speed;

	static ParticleSP Create(float _alpha,glm::vec3 _pos,glm::vec3 _color, glm::vec3 _speed);

	void Draw();
	void Update() {};

	Particle(float _alpha, glm::vec3 _pos,glm::vec3 m_color,glm::vec3 _speed);

};

#endif