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
		printf("�Q�[�����C���V�[������\n");
		printf("\n");
	};

	~GameMainScene()
	{
		printf("�Q�[�����C���V�[���폜\n");
		printf("\n");
	};

};

#endif
