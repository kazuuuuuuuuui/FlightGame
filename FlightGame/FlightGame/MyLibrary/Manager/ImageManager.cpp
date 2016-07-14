#include<assert.h>
#include"ImageManager.h"
#include"../../glut.h"

namespace oka
{
	ImageManager* ImageManager::m_instance = nullptr;

	//-------------------------------------
	//ƒRƒ“ƒXƒgƒ‰ƒNƒ^

	ImageManager::ImageManager()
	{

	}

	//-------------------------------------
	//ƒfƒXƒgƒ‰ƒNƒ^

	ImageManager::~ImageManager()
	{
		m_images.clear();
	}

	//-------------------------------------
	//ˆø”‚Æ‚µ‚ÄŽó‚¯Žæ‚Á‚½ƒeƒNƒXƒ`ƒƒƒnƒ“ƒhƒ‹‚ð
	//ŠÇ—‚µ‚Ä‚¢‚émap‚ÉŠù‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©ŒŸõ‚µ
	//“o˜^‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î“o˜^‚·‚é

	void ImageManager::SetHandle(const std::string _str, const unsigned int _handle)
	{
		if (m_images.find(_str) == m_images.end())
		{
			m_images.insert(std::make_pair(_str, _handle));
		}
	}

	//-------------------------------------
	//ˆø”‚Æ‚µ‚ÄŽó‚¯Žæ‚Á‚½key‚ªmap‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©
	//ŒŸõ‚µ“o˜^‚³‚ê‚Ä‚¢‚ê‚ÎƒeƒNƒXƒ`ƒƒ‚ðíœ‚µ
	//map‚©‚çœŠO‚·‚é

	//void ImageManager::DeleteHandle(const std::string _str)
	//{
		//glDeleteTextures(1, &m_images.find(_str)->second);
		//m_images.erase(_str);
	//}


	//-------------------------------------
	//ˆø”‚Æ‚µ‚ÄŽó‚¯Žæ‚Á‚½key‚ªmap‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©
	//ŒŸõ‚µ“o˜^‚³‚ê‚Ä‚¢‚ê‚Î‚»‚Ìkey‚É‘Î‰ž‚·‚éƒeƒNƒXƒ`ƒƒƒnƒ“ƒhƒ‹‚ð•Ô‚·

	unsigned int ImageManager::GetHandle(const std::string _str)const
	{
		if (m_images.find(_str) == m_images.end())
		{
			assert(0);
			return -1;
		}
		else
		{
			return m_images.find(_str)->second;
		}
	}


}//namespace oka