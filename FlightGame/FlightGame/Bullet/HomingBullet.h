#ifndef HOMINGBULLET_H_
#define HOMINGBULLET_H_

#include"../Bullet/BaseBullet.h"

class HomingBullet;
typedef std::shared_ptr<HomingBullet> HomingBulletSP;

class HomingBullet :public BaseBullet
{
public:
	//bool m_isHoming;
	glm::vec3 m_targetPos;

	static HomingBulletSP Create(glm::vec3 _targetPos, glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed);
	virtual void Draw()override;
	virtual void Update()override;

	HomingBullet(glm::vec3 _targetPos,glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed);
	~HomingBullet();

};

#endif
