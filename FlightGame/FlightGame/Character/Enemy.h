#ifndef ENEMY_H_
#define ENEMY_H_

#include"Character.h"

class Enemy :public Character
{
public:
	glm::vec3 m_aimPos;//–Ú•W“_‚ÌÀ•W

	virtual void Control();
			

	void ResetAimPos();

	//debug
	void DrawAimPos();
	void DrawToAimVec();

	Enemy(glm::vec3 _pos)
	{
		const float x_max = 256.0f;
		m_aimPos.x = ((float)rand() / RAND_MAX)*x_max;
		
		const float bottom = 20.0f;
		m_aimPos.y = bottom + ((float)rand() / RAND_MAX)*10.0f;
		
		const float z_max = -256.0f;
		m_aimPos.z = ((float)rand() / RAND_MAX)*z_max;


		m_transform.m_position = _pos;	
	}

	~Enemy() 
	{
		//debug
		printf("Enemy‚ğíœ‚µ‚Ü‚µ‚½\n");
	};
};

#endif