#ifndef IMAGEMANAGER_H_
#define IMAGEMANAGER_H_

#include<map>
#include<string>
#include"../../\Singleton/Singleton.h"

namespace oka
{
	//-------------------------------------
	//ゲーム中で使用するテクスチャを管理するクラス

	class ImageManager : public Singleton<ImageManager>
	{
		friend class Singleton<ImageManager>;

	public:
		void SetHandle(const std::string _str, const unsigned int _handle);
		//void DeleteHandle(const std::string _str);
		unsigned int GetHandle(const std::string _str)const;

		ImageManager();
		~ImageManager();

	private:
		static ImageManager* m_instance;
		std::map<std::string, unsigned int>m_images;
	};

}

#endif
