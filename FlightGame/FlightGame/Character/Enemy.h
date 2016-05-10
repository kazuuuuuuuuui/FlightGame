#ifndef ENEMY_H_
#define ENEMY_H_

#include"Character.h"

class Enemy :public Character
{
public:
	glm::vec3 m_aimPos;//ñ⁄ïWì_ÇÃç¿ïW

	float m_value;//ï‚äÆÇÃääÇÁÇ©Ç≥

	void Control();
	void Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY) {};
	void MoveToAimPos();
	void SetYaw();
	void SetPitch();

	bool CheckNearAimPis()const;
	void ResetAimPos();

	//debug
	void DrawAimPos();
	void DrawToAimVec();

	Enemy(glm::vec3 _pos) :
		m_value(0.0f)
	{
		const float x_max = 256.0f;
		m_aimPos.x = ((float)rand() / RAND_MAX)*x_max;
		
		const float bottom = 5.0f;
		m_aimPos.y = bottom + ((float)rand() / RAND_MAX)*10.0f;
		
		const float z_max = -256.0f;
		m_aimPos.z = ((float)rand() / RAND_MAX)*z_max;


		m_transform.SetPosition(_pos);
		glm::mat4 translate = glm::mat4(1.0);
		translate = glm::translate(translate,m_transform.GetPosition());
		
		m_transform.m_matrix = translate;
		
	}
};

#endif