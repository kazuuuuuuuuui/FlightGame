#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_

#include<stdio.h>
#include"BaseScene.h"

class GameMainScene:public BaseScene
{
public:
	void Update();
	void Render();

	GameMainScene() 
	{
		printf("ゲームメインシーン生成\n");
		printf("\n");
	};

	~GameMainScene()
	{
		printf("ゲームメインシーン削除\n");
		printf("\n");
	};

};

#endif
