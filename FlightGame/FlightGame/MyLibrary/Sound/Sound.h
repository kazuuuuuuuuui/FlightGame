#ifndef OKA_SOUND_H_
#define OKA_SOUND_H_

#include"../../AL/al.h"
#include"../../AL/alc.h"

#pragma comment(lib,"OpenAL32.lib")

namespace oka
{
	class Sound
	{
	public:
		static void Init();
		static unsigned int LoadWavFile(const char *_wavFileName);
		
	};

}

#endif