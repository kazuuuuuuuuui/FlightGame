#ifndef FEALD_H_
#define FEALD_H_

#include<vector>
#include"../MyLibrary/GameObject/GameObject.h"

//Fealdへのスマートポインタを定義化
class Feald;
typedef std::shared_ptr<Feald> FealdSP;

class Feald :public oka::GameObject 
{
public:
	const int m_width;
	const int m_height;

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
	void Update();

	//debug
	void DrawNormals();

	
	Feald() :
	//変更予定
	m_width(256),
	m_height(256)
	{
		//debug
		printf("フィールドが生成されました\n");
		printf("\n");

		//頂点データ
		SetVertex();

		//インデックスデータ
		SetIndex();

		//頂点の高さ設定
		SetHeight("heightmap.bmp");

		//法線データ
		SetNormal();

		//uvデータ
		SetTex();

	};

	~Feald()
	{
		//debug
		printf("フィールドが削除されました\n");
		printf("\n");
	};

};

#endif

