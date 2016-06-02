#ifndef PLAYER_H_
#define PLAYER_H_

#include"Character.h"
#include"../MyLibrary/Manager/JoysticManager.h"

class Player;
typedef std::shared_ptr<Player> PlayerSP;

class Player :public Character
{
public:
	static PlayerSP Create(glm::vec3 _pos);
	void Control();
	void Accel();
	void Shot();

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