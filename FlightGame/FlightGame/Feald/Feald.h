#ifndef FEALD_H_
#define FEALD_H_

#include"../MyLibrary/GameObject/GameObject.h"

class Feald :public oka::GameObject 
{
public:
	const int m_width;
	const int m_height;

	/*
	
	Meshに書き換え
	
	*/

	//頂点数
	unsigned int m_vertices;

	//インデックス数
	unsigned int m_indeces;

	//頂点情報
	std::vector<glm::vec3>m_vertex;

	//インデックス情報
	std::vector<unsigned short>m_index;

	//法線情報
	std::vector<glm::vec3>m_normal;

	//uv情報
	std::vector<glm::vec2>m_tex;

	void Draw();
	void Update();

	void SetVertex();
	void SetIndex();
	void SetNormal();
	void SetTex();
	void SetHeight(const char *_fileName);


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
		SetHeight("test.bmp");

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

