#include"GameObject.h"

namespace oka
{
	//-------------------------------------
	//自身の持つフレームの更新
	//０F〜３６００Fの間で周期する

	void GameObject::Update()
	{
		m_flame++;

		m_flame %= (60 * 60);
	}

	//-------------------------------------
	//活性状態を返す

	bool GameObject::IsActive()const
	{
		return m_isActive;
	}
}