#ifndef RANKINGSCENE
#define RANKINGSCENE

#include"BaseScene.h"

class RankingScene :public BaseScene
{
public:
	void Update();
	void Render();

	void DrawBackGround();
	void DrawRanking();

	RankingScene();
	virtual ~RankingScene();
};

#endif