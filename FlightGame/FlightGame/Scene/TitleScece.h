#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include<stdio.h>
#include"BaseScene.h"

enum TitleMenu
{
	GameStart = 0,
	Ranking,
	Exit,
	TitleMenuMax
};

class TitleScene :public BaseScene
{
public:
	void Update();
	void Render();

	static int m_titleMeny;
	static const char *m_titleMenyName[TitleMenuMax];

	TitleScene();
	virtual ~TitleScene();
};

#endif
