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
	void HomingShot(unsigned short _downKeys);
	void DrawRadarPos()override;
	void DrawMyScore()const;
	void DrawTarget();
	unsigned int GetMyScore()const;
	void PlusMyScore();
	std::tuple<bool,glm::vec3*> SetTarget();
	
	Player();
	~Player();

private:
	unsigned int m_score;
	oka::Contoroller *m_controller;
	bool m_isRockOn;
	glm::vec3 *m_target;
	


};

#endif