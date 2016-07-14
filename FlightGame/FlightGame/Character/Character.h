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
	virtual void Update() = 0;
	virtual void Control() = 0;
	
	void SetIsHitAttack(bool _isHitAttack);
	bool GetIsHitAttack()const;
	void SetOnRadarPos();
	virtual void DrawRadarPos();
	bool IsGroundOut()const;
	bool IsIntersectGround()const;
	bool IsIntersectSea()const;
	bool IsNear(glm::vec3 _pos,float _distance)const;
	Character();
	
protected:
	oka::MeshSP m_body;
	glm::vec2 m_onRadarPos;
	glm::vec3 m_speed;
	glm::vec3 m_accel;	
	bool m_isHitAttack;
};

#endif