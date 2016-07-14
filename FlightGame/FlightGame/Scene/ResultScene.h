#ifndef RESULTSCENE_H_
#define RESULTSCENE_H_

#include<stdio.h>
#include"BaseScene.h"

enum ResultMenu
{
	ReturnTitle = 0,
	ReturnRanking,
	//RegisterScore,
	ResultMenuMax
};

class ResultScene :public BaseScene
{
public:
	static int m_resultMeny;
	static const char *m_resultMenyName[ResultMenuMax];

	void Update();
	void Render();

	void DrawBackGround();

	ResultScene();
	virtual ~ResultScene();
};

#endif
