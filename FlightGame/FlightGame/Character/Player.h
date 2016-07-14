#ifndef PLAYER_H_
#define PLAYER_H_

#include"Character.h"

class Player;
typedef std::shared_ptr<Player> PlayerSP;

class Player :public Character
{
public:	
	static PlayerSP Create();
	virtual void Update();
	void Control();
	void Control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY);
	void Accel();
	void Accel(unsigned short _pressedKey);
	void Shot();
	void Shot(unsigned short _downKeys);
	void HomingShot();
	void HomingShot(unsigned short _downKeys);
	
	void DrawRadarPos()override;
	void DrawTarget();

	std::tuple<bool,glm::vec3*> SetTarget();
	
	Player();
	~Player();

private:
	oka::Contoroller *m_controller;
	bool m_isRockOn;
	glm::vec3 *m_target;
};

#endif