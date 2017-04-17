#pragma once
#include "RE\ReEng.h"

class MyBoundingBoxClass
{
private:
	bool m_bOrientable = true;
	bool m_isColliding = false;
	MyBoundingBoxClass* m_pNonAligned = nullptr;
	float m_fRadius = 0.0f; //radius of the sphere
	vector3 m_v3CenterLocal = vector3(0.0f); //center of the sphere in local space
	vector3 m_v3CenterGlobal = vector3(0.0f); //center of the sphere in global space
	matrix4 m_m4ToWorld = IDENTITY_M4; //matrix that takes you from local to global space
	MeshManagerSingleton* m_pMeshMngr = nullptr; //for drawing the sphere

	vector3 m_v3Max;
	vector3 m_v3Min;
	vector3 m_v3Size;

	vector3 m_v3MaxG;
	vector3 m_v3MinG;
	vector3 m_v3SizeG;
public:void
	SetColliding(bool input);
	/*
	Sets Center of the sphere in local space
	*/
	void SetCenterLocal(vector3 input);
	/*
	Sets Center of the sphere in global space
	*/
	void SetCenterGlobal(vector3 input);
	/*
	Sets the radius of the sphere
	*/
	void SetRadius(float input);

	/*
	Gets Box verticies
	*/
	std::vector<vector3> GetVerticies(void);
	/*
	Gets center of the sphere in local space
	*/
	vector3 GetCenterLocal(void);
	/*
	Gets center of the sphere in global space
	*/
	vector3 GetCenterGlobal(void);
	/*
	Gets model to world matrix of the sphere
	*/
	matrix4 GetModelMatrix(void);
	/*
	Gets radius of the sphere
	*/
	float GetRadius(void);
	

	vector3 GetGlobalMax();
	vector3 GetGlobalMin();
	/*
	Constructor, needs a vertex list
	*/
	MyBoundingBoxClass(std::vector<vector3> vertexList, bool orientable = true);
	~MyBoundingBoxClass() {
		if (m_pNonAligned != nullptr) delete m_pNonAligned;
	}
	/*
	Sets the transform from the local to world matrix
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);

	/*
	Will check the collision with another object
	*/
	bool IsColliding(MyBoundingBoxClass* a_other);

	void RenderBox();
};