#ifndef _OKA_SOUNDMANAGER_H_
#define _OKA_SOUNDMANAGER_H_

#include<map>
#include<string>
#include"../../Singleton/Singleton.h"

namespace oka
{
	//-------------------------------------
	//�Q�[�����Ŏg�p���鉹���Ǘ�����N���X

	class SoundManager:public Singleton<SoundManager>
	{
		friend Singleton<SoundManager>;

	public:
		void AddSound(const std::string _str, const unsigned int _sound);
		void DeleteSound(const std::string _str);
		void Play(const std::string _str);
		void Stop(const std::string _str);
		void ChangeVolume(const std::string _str, const float _value);
		void ChangePitch(const std::string _str, const float _value);

	private:
		std::map<std::string, unsigned int>m_sounds;
		static SoundManager* m_instance;
		
		SoundManager();
		~SoundManager();
	};

}

#endif