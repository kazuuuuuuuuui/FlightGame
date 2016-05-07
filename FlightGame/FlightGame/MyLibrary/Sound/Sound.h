#ifndef OKA_SOUND_H_
#define OKA_SOUND_H_

#include"../../AL/al.h"
#include"../../AL/alc.h"

namespace oka
{
	class Sound
	{
	public:
		static unsigned int LoadWavFile(const char *_wavFileName);
		
	};

}

#endif