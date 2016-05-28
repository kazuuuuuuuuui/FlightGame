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

		void GameMain(float _delta);
		void Pause(float _delta);
			 
		SceneManager();		

	};
}

#endif