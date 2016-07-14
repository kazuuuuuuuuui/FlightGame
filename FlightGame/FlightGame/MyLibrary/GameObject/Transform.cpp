#include<stdio.h>
#include"Transform.h"
#include"../Camera/Camera.h"
#include"../../glm/gtc/quaternion.hpp"
#include"../../glm/gtx/quaternion.hpp"
#include"../../glm/gtx/transform.hpp"
#include"../../glut.h"

glm::mat4 BillboardMatrix;

namespace oka
{
	//-------------------------------------
	//コンストラクタ

	Transform::Transform() :
		m_matrix(glm::mat4(1.0f)),
		m_position(0.0f, 0.0f, 0.0f),
		m_scale(1.0f, 1.0f, 1.0f),
		m_myToVec(glm::vec3(0.0f, 0.0f, -1.0f)),
		m_myUpVec(glm::vec3(0.0f, 1.0f, 0.0f)),
		m_mySideVec(glm::vec3(1.0f, 0.0f, 0.0f))
	{
		m_rotate.x = 0.0f;
		m_rotate.y = 0.0f;
		m_rotate.z = 0.0f;
		m_rotate.w = 1.0f;
	}


	//-------------------------------------
	//更新

	void Transform::Update()
	{
		//行列計算
		BillboardMatrix = glm::inverse(g_camera->GetViewMatrix());
		BillboardMatrix[3][0] = 0;
		BillboardMatrix[3][1] = 0;
		BillboardMatrix[3][2] = 0;

		//translate
		glm::mat4 translate = glm::translate(m_position);

		glm::mat4 rotate = glm::toMat4(m_rotate);

		//scale
		glm::mat4 scale = glm::scale(m_scale);

		m_matrix = translate * rotate * scale;

		SetAimVec(m_myToVec, glm::vec3(0, 0, -1));
		SetAimVec(m_myUpVec, glm::vec3(0, 1, 0));
		SetAimVec(m_mySideVec, glm::vec3(1, 0, 0));
	}

	//-------------------------------------
	//オブジェクトの向きベクトルの設定
	//引数として設定したい向きベクトルとワールド座標系での向きベクトルを受け取る

	void Transform::SetAimVec(glm::vec3 &_myVec, const glm::vec3 _aimVec)
	{
		//座標行列
		glm::mat4 pos;
		pos = glm::translate(_aimVec);

		glm::mat4 rot = glm::toMat4(m_rotate);

		//向きベクトルを求めるための行列
		glm::mat4 mat;
		mat = rot*pos;

		_myVec.x = mat[3][0];
		_myVec.y = mat[3][1];
		_myVec.z = mat[3][2];

		_myVec = glm::normalize(_myVec);
	}
}//namespace oka