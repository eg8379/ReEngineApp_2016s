#include "MyBoundingObjectClass.h"

MyBoundingObjectClass::MyBoundingObjectClass(std::vector<vector3> verticies)
{
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_Box = new MyBoundingBoxClass(verticies);
	m_Sphere = new MyBoundingSphereClass(m_Box->GetReorientedBox()->GetVerticies());
}

MyBoundingObjectClass::~MyBoundingObjectClass()
{
	delete m_Box;
	delete m_Sphere;
}

void MyBoundingObjectClass::SetVisible(bool visible) { m_Visible = visible; }

bool MyBoundingObjectClass::GetVisible() { return m_Visible; }

vector3 MyBoundingObjectClass::GetGlobalCenter()
{
	return m_GlobalCenter;
}

vector3 MyBoundingObjectClass::GetGlobalBoxMinimum()
{
	return m_Box->GetGlobalMax();
}

vector3 MyBoundingObjectClass::GetGlobalBoxMaximum()
{
	return m_Box->GetGlobalMin();
}

void MyBoundingObjectClass::SetModelMatrix(matrix4 toWorld)
{
	if (toWorld == m_WorldTransform) return;
	m_WorldTransform = toWorld;
	m_Box->SetModelMatrix(toWorld);

	delete m_Sphere;
	m_Sphere = new MyBoundingSphereClass(m_Box->GetReorientedBox()->GetVerticies());
	//m_Sphere->SetModelMatrix(toWorld);
}

matrix4 MyBoundingObjectClass::GetModelMatrix()
{
	return m_WorldTransform;
}

void MyBoundingObjectClass::SetColor(vector3 rgb) { m_Color = rgb; }
vector3 MyBoundingObjectClass::GetColor() { return m_Color; }
void MyBoundingObjectClass::SetCollidingColor(vector3 rgb) { m_HitColor = rgb; }
vector3 MyBoundingObjectClass::GetCollidingColor() { return m_HitColor; }

MyBoundingSphereClass* MyBoundingObjectClass::GetSphere()
{
	return m_Sphere;
}

MyBoundingBoxClass* MyBoundingObjectClass::GetBox()
{
	return m_Box;
}

void MyBoundingObjectClass::Render()
{
	vector3 v3Color = m_Color;
	if (m_Colliding)
		v3Color = m_HitColor;

	/*m_pMeshMngr->AddCubeToRenderList(
		m_WorldTransform *
		glm::translate(m_LocalCenter) *
		glm::scale(GetGlobalBoxMaximum()-GetGlobalBoxMinimum()),
		v3Color, WIRE);

	m_pMeshMngr->AddSphereToRenderList(
		m_WorldTransform *
		glm::translate(m_LocalCenter) *
		glm::scale(vector3(GetGlobalBoxMaximum() - GetGlobalBoxMinimum())), v3Color, WIRE);*/

	m_Box->RenderSphere();
	m_Sphere->RenderSphere();
}

void MyBoundingObjectClass::SetColliding(bool colliding)
{
	m_Box->SetColliding(colliding);
	m_Sphere->SetColliding(colliding);
	m_Colliding = colliding;
}

bool MyBoundingObjectClass::IsColliding(MyBoundingObjectClass* other)
{
	return m_Sphere->IsColliding(other->GetSphere()) && m_Box->IsColliding(other->GetBox());
}
