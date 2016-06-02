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
		printf("ポーズシーン生成\n");
		printf("\n");
	};

	~PauseScene()
	{
		//debug
		printf("ポーズシーン削除\n");
		printf("\n");
	};

};

#endif