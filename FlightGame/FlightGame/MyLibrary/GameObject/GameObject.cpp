#include"GameObject.h"

namespace oka
{
	//-------------------------------------
	//©gÌÂt[ÌXV
	//OF`RUOOFÌÔÅüú·é

	void GameObject::Update()
	{
		m_flame++;

		m_flame %= (60 * 60);
	}

	//-------------------------------------
	//

	bool GameObject::IsActive()const
	{
		return m_isActive;
	}
}