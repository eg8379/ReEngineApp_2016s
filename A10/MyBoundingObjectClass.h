#pragma once
#include "MyBoundingSphereClass.h"
#include "MyBoundingBoxClass.h"

/*
At a bare minimum the MyBoundingObjectClass should let the user:

-Add a BO based on a model (by its list of vertices) (done through constructor)
-Switch the visibility of the BO (GetterSetter and Render if)
-Get the Centroid (in world coordinates) of the BO (center of sphere)
-Get the Minimum and Maximum of the BO (reoriented global)
-Get and Set the “Model to World” matrix of the BO
-Set the color of the BO
-Draw the BO (if you are working with ReEngine, add it to the render list)
-Check the collision with other BOs
*/
class MyBoundingObjectClass
{
private:
	MyBoundingSphereClass* m_Sphere = nullptr;
	MyBoundingBoxClass* m_Box = nullptr;
	
	vector3 m_Color = REGREEN;
	vector3 m_HitColor = RERED;
	bool m_Visible = true;

	bool m_Colliding = false;

	vector3 m_LocalCenter = vector3(0.f);
	vector3 m_GlobalCenter = vector3(0.f);
	matrix4 m_WorldTransform = IDENTITY_M4;

	MeshManagerSingleton* m_pMeshMngr = nullptr;

public:
	MyBoundingObjectClass(std::vector<vector3> verticies);
	~MyBoundingObjectClass();

	void SetVisible(bool visible);
	bool GetVisible();
	
	vector3 GetGlobalCenter();
	vector3 GetGlobalBoxMinimum();
	vector3 GetGlobalBoxMaximum();

	void SetModelMatrix(matrix4 toWorld);
	matrix4 GetModelMatrix();

	void SetColor(vector3 rgb);
	vector3 GetColor();
	void SetCollidingColor(vector3 rgb);
	vector3 GetCollidingColor();

	MyBoundingSphereClass* GetSphere();
	MyBoundingBoxClass* GetBox();

	void Render();

	void SetColliding(bool colliding);
	void CheckCollisions(MyBoundingObjectClass* other);
};

