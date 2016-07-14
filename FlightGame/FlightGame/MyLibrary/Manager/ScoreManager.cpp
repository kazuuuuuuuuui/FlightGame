#include<stdio.h>
#include<algorithm>
#include<functional>
#include"ScoreManager.h"
#include"CharacterManager.h"
#include"../Screen/Screen.h"
#include"../../glut.h"

namespace oka
{
	ScoreManager* ScoreManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^

	ScoreManager::ScoreManager()
	{	
		ImportRankingScore("Ranking.txt");
	}

	//-------------------------------------
	//�f�X�g���N�^

	ScoreManager::~ScoreManager()
	{
		m_rankingScore.clear();
	}	

	//-------------------------------------
	//���݂̃X�R�A��Ԃ�

	int ScoreManager::GetScore()const
	{
		return m_score;
	}

	//-------------------------------------
	//�����L���O�̃X�R�A��Ԃ�
	//�����Ƃ��ăR���e�i�̓Y�������󂯎��

	int ScoreManager::GetRankingScore(const int _num)const
	{
		return m_rankingScore[_num];
	}

	//-------------------------------------
	//�X�R�A���C���N�������g����

	void ScoreManager::PlusScore()
	{
		m_score++;
	}

	//-------------------------------------
	//���g�̃X�R�A��\������

	void ScoreManager::DrawScore()const
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			char buf[256];

			const int width = oka::Screen::GetInstance()->GetWidth() / 10 - 50;
			const int height = oka::Screen::GetInstance()->GetHeight() - oka::Screen::GetInstance()->GetHeight() / 8;


			sprintf_s(buf, "Hit:%d", m_score);

			glColor3f(0.0f, 0.0f, 0.0f);
			glLineWidth(2);

			glPushMatrix();
			{
				glTranslatef(width, height, 0.0f);
				glScalef(0.5f, 0.5f, 0.5f);

				for (unsigned int i = 0; i < strlen(buf); i++)
				{
					glutStrokeCharacter(GLUT_STROKE_ROMAN, buf[i]);
				}
			}
			glPopMatrix();
		}
		glPopAttrib();
	}

	//-------------------------------------
	//�����L���O�̃X�R�A���O���t�@�C����
	//�e�L�X�g�f�[�^����ǂݍ���

	void ScoreManager::ImportRankingScore(const char *_fileName)
	{
		FILE *fp;
		fopen_s(&fp, _fileName, "r");

		if (nullptr == fp)
		{
			assert(0);
		}

		int rankingScore;
		while (fscanf_s(fp, "%d", &rankingScore) != EOF)
		{
			m_rankingScore.push_back(rankingScore);
		}

		fclose(fp);
	}

	//-------------------------------------
	//

	void ScoreManager::ExportRankingScore(const char *_fileName)
	{
		FILE *fp;
		fopen_s(&fp, _fileName, "w");

		if (nullptr == fp)
		{
			assert(0);
		}

		//�����L���O�̃X�R�A���~���Ń\�[�g
		std::sort(m_rankingScore.begin(), m_rankingScore.end(), std::greater<int>());

		const int indexLast = m_rankingScore.size() - 1;
		const int bottomNum = m_rankingScore[indexLast];

		if (m_score > bottomNum)
		{
			m_rankingScore[indexLast] = m_score;
		}

		std::sort(m_rankingScore.begin(), m_rankingScore.end(), std::greater<int>());

		for (unsigned int i = 0; i < m_rankingScore.size(); i++)
		{
			const int score = m_rankingScore[i];
			fprintf_s(fp, "%d\n", score);
		}

		fclose(fp);
	}

}