#ifndef TIMEUPSCENE_H_
#define TIMEUPSCENE_H_

#include"BaseScene.h"

class TimeUpScene :public BaseScene
{
public:
	void Update();
	void Render();

	TimeUpScene();
	virtual ~TimeUpScene();
};

#endif
