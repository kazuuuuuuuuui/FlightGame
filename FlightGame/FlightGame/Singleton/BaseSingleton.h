#ifndef BASESINGLETON_H_
#define BASESINGLETON_H_

#include<vector>

class BaseSingleton
{
public:
	static void Update();
	virtual void Destroy() = 0;
	static void AllDestroy();
	static void Clear();
	BaseSingleton();

private:
	static std::vector<BaseSingleton*>m_singletons;
};

#endif