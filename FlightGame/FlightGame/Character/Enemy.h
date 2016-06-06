#ifndef ENEMY_H_
#define ENEMY_H_

#include"Character.h"

class Enemy;
typedef std::shared_ptr<Enemy> EnemySP;

class Enemy :public Character
{
public:
	glm::vec3 m_aimPos;//–Ú•W“_‚ÌÀ•W

	static EnemySP Create(glm::vec3 _pos);
	virtual void Update();
	virtual void Control();
	void Shot();

	void ResetAimPos();

	Enemy(glm::vec3 _pos);
	~Enemy() 
	{
		//debug
		printf("Enemy‚ğíœ‚µ‚Ü‚µ‚½\n");
	};
};

#endif