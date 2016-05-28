#ifndef BULLET_H_
#define BULLET_H_

#include"../MyLibrary/GameObject/GameObject.h"

class Bullet :public oka::GameObject
{
public:
	glm::vec3 m_speed;

	static Bullet* Create(glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed);
	void Draw();
	void Update();
	bool IsHit(glm::vec3 _pos)const;
	bool IsGroundOut()const;
	bool IsIntersectGround()const;

		
	Bullet();
	~Bullet();

};

#endif
