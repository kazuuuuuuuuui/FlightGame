#ifndef BASESCENE_H_
#define BASESCENE_H_

class BaseScene
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	BaseScene() {};
	~BaseScene() {};
};

#endif