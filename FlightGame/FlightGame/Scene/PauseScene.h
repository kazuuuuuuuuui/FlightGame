#ifndef PAUSESCENE_H_
#define PAUSESCENE_H_

#include<stdio.h>
#include<string>
#include"BaseScene.h"

class PauseScene :public BaseScene
{
public:
	enum Selection
	{
		BackGameMain = 0,
		Exit,
		SelectionMax
	};

	static int m_nowSelect;
	static const char *m_selections[SelectionMax];

	void Update();
	void Render();

	PauseScene()
	{
		//debug
		printf("�|�[�Y�V�[������\n");
		printf("\n");
	};

	~PauseScene()
	{
		//debug
		printf("�|�[�Y�V�[���폜\n");
		printf("\n");
	};

};

#endif