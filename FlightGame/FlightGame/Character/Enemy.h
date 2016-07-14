#ifndef ENEMY_H_
#define ENEMY_H_

#include"Character.h"
#include"../MyLibrary/Input/VirtualController.h"

class Enemy;
typedef std::shared_ptr<Enemy> EnemySP;

class Enemy :public Character
{
public:
	static EnemySP Create();
	virtual void Update();
	virtual void Control();
	bool IsFrontPlayer(glm::vec3 _pos)const;
	void Shot();
	void Patrol();
	void Chase();
	void Fall();
	void ResetAimPos();

	Enemy();

private:
	glm::vec3 m_aimPos;
	VirtualController m_controller;

};

#endif