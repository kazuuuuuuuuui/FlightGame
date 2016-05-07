#ifndef OKA_WAVFILE_H_
#define OKA_WAVFILE_H_

namespace oka
{

	//wavファイルの構造
	struct WavFile
	{
		char m_riff[4];              // = "RIFF"
		unsigned int m_file_size;    // 全体サイズ
		char m_fmt[8];               // "WAVEfmt "
		unsigned int m_fmt_size;      // fmt チャンクサイズ
		unsigned short  m_format;       // フォーマットの種類
		unsigned short  m_channel;      // チャンネル
		unsigned int   m_rate;         // サンプリングレート
		unsigned int   m_avgbyte;      // rate * block
		unsigned short  m_block;        // channels * bit / 8
		unsigned short  m_bit;          // ビット数
		char m_data[4];               // = "data"
		unsigned int m_data_size;      // データサイズ

	};

}

#endif