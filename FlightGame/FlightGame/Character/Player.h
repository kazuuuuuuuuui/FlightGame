#ifndef PLAYER_H_
#define PLAYER_H_

#include"Character.h"
#include"../MyLibrary/Manager/JoysticManager.h"

class Player;
typedef std::shared_ptr<Player> PlayerSP;

class Player :public Character
{
public:
	oka::Contoroller *m_controller;

	static PlayerSP Create(glm::vec3 _pos);
	virtual void Update();
	void Control();
	void Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY);
	void Accel();
	void Accel(unsigned short _pressedKey);
	void Shot();
	void Shot(unsigned short _downKeys);

	//test
	void HomingShot(unsigned short _downKeys);
	glm::vec3 m_targetPos;

	bool IsNear(glm::vec3 _pos)const;
	void DrawTarget();
	std::tuple<bool,glm::vec3> SetTarget();
	
	Player(glm::vec3 _pos);
	~Player();
};

#endif