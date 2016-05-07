#ifndef BULLET_H_
#define BULLET_H_

#include"../MyLibrary/GameObject/GameObject.h"

class Bullet :public oka::GameObject
{
public:
	unsigned int m_attack;
	glm::vec3 m_speed;
	bool m_isHorming;

	void Draw();
	void Update();
	bool CheckIsHit(glm::vec3 _pos)const;
	bool CheckNearCharacter(glm::vec3 _pos)const;

	//ホーミングの方に移す
	void Homing(glm::vec3 _pos);

	//debug
	void DrawToEnemyVec();

	
		
		Bullet() {};
	Bullet(glm::vec3 _pos, glm::vec3 _rotate, glm::vec3 _speed):
		m_speed(glm::vec3(0.0f, 0.0f, 0.0f)),
		m_attack(5),
		m_isHorming(true)
	{
		m_transform.SetPosition(_pos);
		m_transform.SetRotation(_rotate);
		m_speed = _speed;
	}

};

#endif
