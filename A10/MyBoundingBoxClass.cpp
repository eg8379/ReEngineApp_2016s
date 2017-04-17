#include "MyBoundingBoxClass.h"

vector3 MyBoundingBoxClass::GetGlobalMax()
{
	return m_v3MaxG;
}

vector3 MyBoundingBoxClass::GetGlobalMin()
{
	return m_v3MinG;
}
void MyBoundingBoxClass::SetColliding(bool input) {
	m_isColliding = input;
	if (m_bOrientable) m_pNonAligned->SetColliding(input);
}
void MyBoundingBoxClass::RenderBox()
{
	vector3 v3Color = REGREEN;
	if (true == m_isColliding)
		v3Color = REBLUE;

	m_pMeshMngr->AddCubeToRenderList(
		m_m4ToWorld *
		glm::translate(m_v3CenterLocal) *
		glm::scale(m_v3Size),
		v3Color, WIRE);

	if (m_pNonAligned != nullptr) m_pNonAligned->RenderBox();
}
MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList, bool orientable)
{
	m_bOrientable = orientable;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

	if (vertexList.size() < 1)
		return;

	m_v3Min = vertexList[0];
	m_v3Max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;

	m_v3MinG = m_v3Min;
	m_v3MaxG = m_v3Max;
	if (m_bOrientable)
	{
		m_pNonAligned = new MyBoundingBoxClass(GetVerticies(), false);
	}
}

void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (!m_bOrientable || m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
	m_v3MinG = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	m_v3MaxG = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
	
	if (m_pNonAligned != nullptr) delete m_pNonAligned;
	m_pNonAligned = new MyBoundingBoxClass(GetVerticies(), false);
}

bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* a_other)
{
	if (m_bOrientable) {
		return m_pNonAligned->IsColliding(a_other);
	}
	if (this->m_v3MaxG.x < a_other->m_v3MinG.x)
		return false;
	if (this->m_v3MinG.x > a_other->m_v3MaxG.x)
		return false;

	if (this->m_v3MaxG.y < a_other->m_v3MinG.y)
		return false;
	if (this->m_v3MinG.y > a_other->m_v3MaxG.y)
		return false;

	if (this->m_v3MaxG.z < a_other->m_v3MinG.z)
		return false;
	if (this->m_v3MinG.z > a_other->m_v3MaxG.z)
		return false;

	return true;
}

std::vector<vector3> MyBoundingBoxClass::GetVerticies(void)
{
	std::vector<vector3> points;
	for (unsigned char i = 0; i < 8; i++)
	{
		points.push_back(vector3(((i % 2 == 0 ? m_v3Min : m_v3Max).x), (((i >> 1) % 2 == 0 ? m_v3Min : m_v3Max).y), (((i >> 2) % 2 == 0 ? m_v3Min : m_v3Max).z)));
		points[i] = vector3(m_m4ToWorld * vector4(points[i], 1.0f));
	}
	return points;
}