#ifndef EXPLODE_H_
#define EXPLODE_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"
#include"Smoke.h"
#include"Fire.h"

class Explode :public oka::GameObject
{
public:
	Fire *m_fire;
	Smoke *m_smoke;
	
	static Explode* Create(glm::vec3 _pos);

	void Draw();
	void Update();

	Explode(glm::vec3 _pos);
};

#endif