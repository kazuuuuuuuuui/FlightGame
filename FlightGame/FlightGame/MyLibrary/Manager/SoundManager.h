#ifndef _OKA_SOUNDMANAGER_H_
#define _OKA_SOUNDMANAGER_H_

#include<map>
#include<string>

namespace oka
{
	//-------------------------------------
	//ゲーム中で使用する音を管理するクラス

	class SoundManager
	{
	private:
		std::map<std::string, unsigned int>m_sounds;
		static SoundManager* m_instance;
		
		SoundManager() {}
		~SoundManager() {}

	public:
		
		static SoundManager* GetInstance();
		void AddSound(const std::string _str, const unsigned int _sound);
		void DeleteSound(const std::string _str);
		void Play(const std::string _str);
		void Stop(const std::string _str);
		void ChangeVolume(const std::string _str,const float _value);
		void ChangePitch(const std::string _str, const float _value);
	};

}

#endif