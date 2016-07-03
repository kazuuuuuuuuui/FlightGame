#ifndef FEALD_H_
#define FEALD_H_

#include<vector>
#include"../MyLibrary/GameObject/GameObject.h"

class Feald;
typedef std::shared_ptr<Feald> FealdSP;

class Feald :public oka::GameObject 
{
public:
	const int m_width;
	const int m_height;
	const glm::vec3 m_leftBottom;
	const glm::vec3 m_rightBottom;
	const glm::vec3 m_leftTop;
	const glm::vec3 m_rightTop;

	unsigned int m_vertices;
	unsigned int m_indeces;
	std::vector<glm::vec3>m_vertex;
	std::vector<unsigned short>m_index;
	std::vector<glm::vec3>m_normal;
	std::vector<glm::vec2>m_tex;

	static FealdSP Create();
	void SetVertex();
	void SetIndex();
	void SetNormal();
	void SetTex();
	void SetHeight(const char *_fileName);
	void Draw();

	Feald();
	~Feald();

};

#endif

