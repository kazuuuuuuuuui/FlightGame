#ifndef BULLET_H_
#define BULLET_H_

#include"../Bullet/BaseBullet.h"

class Bullet;
typedef std::shared_ptr<Bullet> BulletSP;

class Bullet :public BaseBullet
{
public:
	static BulletSP Create(glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed);
	virtual void Draw()override;
	virtual void Update()override;
		
	Bullet(glm::vec3 _pos, glm::mat4 _rotate, glm::vec3 _speed);
	~Bullet();

};

#endif
