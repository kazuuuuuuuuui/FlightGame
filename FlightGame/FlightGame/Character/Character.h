#ifndef CHARACTER_H_
#define CHARACTER_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"
#include"../MyLibrary/GameObject/Mesh.h"
#include"../MyLibrary/Input/Controller.h"
#include"../Bullet/Bullet.h"

class Character :public oka::GameObject
{
public:
	oka::Mesh *m_body;
	oka::Mesh *m_propeller;
	
	oka::Contoroller *m_controller;

	bool m_isHitAttack;
	unsigned int m_hp;

	glm::vec3 m_speed;
	glm::vec3 m_accel;

	void Draw() {};
	void Update();
	virtual void Control() = 0;
	virtual void Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY) = 0;
	bool CheckIsDead()const;

	Character();
};

#endif