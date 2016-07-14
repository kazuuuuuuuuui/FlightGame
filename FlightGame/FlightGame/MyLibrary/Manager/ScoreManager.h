#ifndef SCORE_MANAGER_
#define SCORE_MANAGER_

#include<vector>
#include"../../Singleton/Singleton.h"

namespace oka
{
	class ScoreManager : public Singleton<ScoreManager>
	{
		friend class Singleton<ScoreManager>;

	public:
		int GetScore()const;
		int GetRankingScore(const int _num)const;
		void PlusScore();
		void DrawScore()const;
		void ImportRankingScore(const char *_fileName);
		void ExportRankingScore(const char *_fileName);

		ScoreManager();
		~ScoreManager();

	private:
		static ScoreManager* m_instance;
		int m_score;
		std::vector<int>m_rankingScore;
	};
}

#endif