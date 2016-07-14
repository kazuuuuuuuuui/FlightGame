#ifndef BASESCENE_H_
#define BASESCENE_H_

class BaseScene
{
public:
	virtual void Update() {};
	virtual void Render() {};

	BaseScene() {};
	virtual ~BaseScene() {};
};

#endif