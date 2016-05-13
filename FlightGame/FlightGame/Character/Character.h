#ifndef CHARACTER_H_
#define CHARACTER_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"
#include"../MyLibrary/Input/Controller.h"
#include"../MyLibrary/Model/xFile.h"
#include"../Bullet/Bullet.h"
//#include"../Bullet/HomingBullet.h"

class Character :public oka::GameObject
{
public:
	//oka::xFile *m_body;
	oka::Contoroller *m_controller;

	bool m_isHitAttack;
	unsigned int m_hp;

	glm::vec3 m_speed;
	glm::vec3 m_accel;

	void Draw();
	void Update();
	virtual void Control() = 0;
	virtual void Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY) = 0;
	bool CheckIsDead()const;

	Character();
};

#endif