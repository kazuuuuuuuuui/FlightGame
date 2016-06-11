#ifndef _OKA_BMPIMAGE_H_
#define _OKA_BMPIMAGE_H_

namespace oka 
{
	//-------------------------------------
	//画像ファイルのピクセル構造体
	//RGB   透過度無し
	//RGBA　透過度有り

	struct RGB
	{
		unsigned char r, g, b;
	};

	struct RGBA
	{
		unsigned char r, g, b, a;
	};

	//-------------------------------------
	//

	unsigned int LoadImage3f(const char *_fileName);
	unsigned int LoadImage4f(const char *_filename, bool _grayscale);

}

#endif