#ifndef HOMINGBULLET_H_
#define HOMINGBULLET_H_

#include<vector>
#include"../Bullet/BaseBullet.h"
#include"../MyLibrary/GameObject/Mesh.h"

class HomingBullet;
typedef std::shared_ptr<HomingBullet> HomingBulletSP;

class HomingBullet :public BaseBullet
{
public:
	static HomingBulletSP Create(glm::vec3 *_target, glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed);
	virtual void Draw()override;
	virtual void Update()override;
	void SetHomingSpeed();

	HomingBullet(glm::vec3 *_target,glm::vec3 _pos, glm::tquat<float> _rotate, glm::vec3 _speed);
	~HomingBullet();

private:
	bool m_isHoming;
	glm::vec3 *m_target;
};

#endif
