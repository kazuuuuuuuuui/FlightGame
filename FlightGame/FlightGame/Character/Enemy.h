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

	//test
	void Draw();

	Enemy();
	~Enemy()
	{
		//debug
		//printf("Enemy‚ğíœ‚µ‚Ü‚µ‚½\n");
	};

private:
	VirtualController m_Controller;
	glm::vec3 m_aimPos;

};

#endif