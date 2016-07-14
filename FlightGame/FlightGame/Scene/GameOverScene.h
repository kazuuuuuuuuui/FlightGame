#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include"BaseScene.h"

class GameOverScene :public BaseScene
{
public:
	void Update();
	void Render();

	GameOverScene();
	virtual ~GameOverScene();
};

#endif
