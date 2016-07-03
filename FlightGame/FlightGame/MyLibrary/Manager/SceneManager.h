#ifndef OKA_SCENEMANAGER_H_
#define OKA_SCENEMANAGER_H_

#include"Sequence.h"
#include"../../Scene/BaseScene.h"

namespace oka
{
	class SceneManager
	{
	public:
		void Update();
		Sequence<SceneManager> m_sequence;
		BaseScene *m_nowScene;
		BaseScene *m_prevScene;


		static SceneManager* GetInstance();

	private:
		static SceneManager* m_instance;

		void Title(float _delta);
		void Game(float _delta);
		void TimeUp(float _delta);
		void GameOver(float _delta);
		void Result(float _delta);
		void End(float _delta);
			 
		SceneManager();		

	};
}

#endif