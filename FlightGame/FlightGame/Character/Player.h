#ifndef PLAYER_H_
#define PLAYER_H_

#include"Character.h"

class Player :public Character
{
public:
	void Control();
	void Accel();
	void Yaw();
	void Roll();
	void Pitch() {};
	void Shot();

	void Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY);
	void Accel(unsigned short _pressedKey);
	void Yaw(float _sThumbLX);
	void Pitch(float _sThumbLY);
	void Roll(unsigned short _pressedKey);
	void Shot(unsigned short _downKeys);

	void DrawTarget();

	/*
	
	ゲームパッドで回転から開始
	
	*/


	Player(glm::vec3 _pos)
	{
		m_transform.SetPosition(_pos);
		glm::mat4 translate = glm::mat4(1.0);
		translate = glm::translate(translate, m_transform.GetPosition());

		m_transform.m_matrix = translate;
	}
};

#endif