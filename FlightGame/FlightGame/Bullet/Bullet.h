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
	Bullet(glm::vec3 _pos, glm::vec3 _speed, glm::mat4 _rotate):
		m_attack(5),
		m_speed(_speed),
		m_isHorming(true)
	{
		m_transform.m_position = _pos;
		m_transform.m_rotate = _rotate;
	}

	~Bullet();

};

#endif
