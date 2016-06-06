#ifndef CHARACTER_H_
#define CHARACTER_H_

#include<list>
#include"../MyLibrary/GameObject/GameObject.h"
#include"../MyLibrary/GameObject/Mesh.h"
#include"../MyLibrary/Input/Controller.h"
#include"../Bullet/Bullet.h"

class Character;
typedef std::shared_ptr<Character> CharacterSP;

class Character :public oka::GameObject
{
public:
	oka::MeshSP m_body;
	oka::MeshSP m_propeller;	

	glm::vec2 m_onRadarPos;
	bool m_isHitAttack;
	unsigned int m_hp;

	glm::vec3 m_speed;
	glm::vec3 m_accel;

	virtual void Update() = 0;
	virtual void Control() = 0;
	
	void SetOnRadarPos();
	bool IsGroundOut()const;
	bool IsIntersectGround()const;
	bool IsDead()const;

	Character();
};

#endif