#ifndef ENEMY_H_
#define ENEMY_H_

#include"Character.h"

class Enemy;
typedef std::shared_ptr<Enemy> EnemySP;

class Enemy :public Character
{
public:
	glm::vec3 m_aimPos;//目標点の座標

	static EnemySP Create(glm::vec3 _pos);
	virtual void Update();
	virtual void Control();
	void Shot();

	void ResetAimPos();

	Enemy(glm::vec3 _pos);
	~Enemy() 
	{
		//debug
		printf("Enemyを削除しました\n");
	};
};

#endif