#ifndef PLAYER_H_
#define PLAYER_H_

#include"Character.h"

class Player :public Character
{
public:
	void Control();
	void Accel();
	void Shot();

	void Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY);
	void Accel(unsigned short _pressedKey);
	void Shot(unsigned short _downKeys);

	void DrawTarget();

	Player(glm::vec3 _pos)
	{
		m_transform.m_position = _pos;
	}

	~Player()
	{
printf("PlayerçÌèú\n");
	}
};

#endif