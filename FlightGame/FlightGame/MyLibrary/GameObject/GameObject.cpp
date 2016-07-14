#include"GameObject.h"

namespace oka
{
	//-------------------------------------
	//©g‚Ì‚ÂƒtƒŒ[ƒ€‚ÌXV
	//‚OF`‚R‚U‚O‚OF‚ÌŠÔ‚ÅüŠú‚·‚é

	void GameObject::Update()
	{
		m_flame++;

		m_flame %= (60 * 60);
	}

	//-------------------------------------
	//Šˆ«ó‘Ô‚ğ•Ô‚·

	bool GameObject::IsActive()const
	{
		return m_isActive;
	}
}