#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_

#include<stdio.h>
#include"BaseScene.h"

class GameMainScene:public BaseScene
{
public:
	void Update();
	void Render();

	GameMainScene();
	virtual ~GameMainScene();
};

#endif
