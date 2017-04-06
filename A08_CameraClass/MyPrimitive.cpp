#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
//C
//|\
//| \
//A--B
//This will make the triang A->B->C
void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTop);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here

	//Create points
	vector3 peak(0.0f, a_fHeight/2, 0.0f);
	vector3 baseCenter(0.0f, -a_fHeight/2, 0.0f);
	std::vector<vector3> baseRing(a_nSubdivisions);
	for (int i = 0; i < a_nSubdivisions; i += 1)
	{
		baseRing[i] = vector3(a_fRadius*cos(i*2.0f*PI / a_nSubdivisions), -a_fHeight/2, a_fRadius*sin(i*2.0f*PI / a_nSubdivisions));
	}
	//Connect points
	for (int i = 0; i < a_nSubdivisions; i += 1)
	{
		AddTri(baseCenter, baseRing[i], baseRing[(i+1)%a_nSubdivisions]);
		AddTri(peak, baseRing[(i + 1) % a_nSubdivisions], baseRing[i]);
	}
	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here

	//Create points
	vector3 lowCenter(0.0f, -a_fHeight/2, 0.0f);
	std::vector<vector3> lowRing(a_nSubdivisions);
	vector3 highCenter(0.0f, a_fHeight/2, 0.0f);
	std::vector<vector3> highRing(a_nSubdivisions);
	for (int i = 0; i < a_nSubdivisions; i += 1)
	{
		lowRing[i] = vector3(a_fRadius*cos(i*2.0f*PI / a_nSubdivisions), -a_fHeight/2, a_fRadius*sin(i*2.0f*PI / a_nSubdivisions));
		highRing[i] = lowRing[i] + vector3(0.0f, a_fHeight, 0.0f);
	}

	//Connect Points
	for (int i = 0; i < a_nSubdivisions; i += 1)
	{
		AddTri(lowCenter, lowRing[i], lowRing[(i + 1) % a_nSubdivisions]);
		AddQuad(highRing[i], highRing[(i + 1) % a_nSubdivisions], lowRing[i], lowRing[(i + 1) % a_nSubdivisions]);
		AddTri(highCenter, highRing[(i + 1) % a_nSubdivisions], highRing[i]);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
Init();

//Your code starts here
//Create points
std::vector<vector3> lowInner(a_nSubdivisions);
std::vector<vector3> lowOuter(a_nSubdivisions);
std::vector<vector3> highInner(a_nSubdivisions);
std::vector<vector3> highOuter(a_nSubdivisions);
for (int i = 0; i < a_nSubdivisions; i += 1)
{
	lowInner[i] = vector3(a_fInnerRadius*cos(i*2.0f*PI / a_nSubdivisions), -a_fHeight / 2, a_fInnerRadius*sin(i*2.0f*PI / a_nSubdivisions));
	lowOuter[i] = vector3(a_fOuterRadius*cos(i*2.0f*PI / a_nSubdivisions), -a_fHeight / 2, a_fOuterRadius*sin(i*2.0f*PI / a_nSubdivisions));

	highInner[i] = lowInner[i] + vector3(0.0f, a_fHeight, 0.0f);
	highOuter[i] = lowOuter[i] + vector3(0.0f, a_fHeight, 0.0f);
}

//Connect Points
for (int i = 0; i < a_nSubdivisions; i += 1)
{
	AddQuad(highOuter[i], highOuter[(i + 1) % a_nSubdivisions], lowOuter[i], lowOuter[(i + 1) % a_nSubdivisions]);
	AddQuad(lowOuter[i], lowOuter[(i + 1) % a_nSubdivisions], lowInner[i], lowInner[(i + 1) % a_nSubdivisions]);
	AddQuad(lowInner[i], lowInner[(i + 1) % a_nSubdivisions], highInner[i], highInner[(i + 1) % a_nSubdivisions]);
	AddQuad(highInner[i], highInner[(i + 1) % a_nSubdivisions], highOuter[i], highOuter[(i + 1) % a_nSubdivisions]);
}

//Your code ends here
CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here

	float torusThickness = (a_fOuterRadius - a_fInnerRadius) / 2;
	float torusRadius = (a_fOuterRadius + a_fInnerRadius) / 2;

	std::vector<std::vector<vector3>> rings(a_nSubdivisionsB);

	for (int i = 0; i < a_nSubdivisionsB; i += 1)
	{
		//make ring
		rings[i] = std::vector<vector3>(a_nSubdivisionsA);
		for (int j = 0; j < a_nSubdivisionsA; j += 1)
		{
			rings[i][j] = vector3(torusRadius + torusThickness*cos((j + 1)*2.f*PI / a_nSubdivisionsA), torusThickness*sin((j + 1)*2.f*PI / a_nSubdivisionsA), 0.0f);
			rings[i][j] = glm::rotateY(rings[i][j], (float)(i*360.f / a_nSubdivisionsB));
		}
	}

	//connect points

	for (int i = 0; i < a_nSubdivisionsB; i += 1)
	{
		for (int j = 0; j < a_nSubdivisionsA; j += 1)
		{
			AddQuad(rings[i][j], rings[(i + 1) % a_nSubdivisionsB][j], rings[i][(j + 1) % a_nSubdivisionsA], rings[(i + 1) % a_nSubdivisionsB][(j + 1) % a_nSubdivisionsA]);
		}
	}
	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here

	//create points
	vector3 peak = vector3(0.0f, a_fRadius, 0.0f);
	vector3 antiPeak = vector3(0.0f, -a_fRadius, 0.0f);
	int halfRingCount = 1 << (a_nSubdivisions+1);
	int partitions = (1 << a_nSubdivisions);
	std::vector<std::vector<vector3>> rings(halfRingCount);

	for (int i = 0; i < halfRingCount; i += 1)
	{
		//make ring
		rings[i] = std::vector<vector3>(partitions-1);
		for (int j = 0; j < partitions-1; j += 1)
		{
			rings[i][j] = vector3( a_fRadius*cos(-PI / 2.f + (j + 1)*PI / partitions), a_fRadius*sin(-PI / 2.f + (j + 1)*PI / partitions), 0.0f);
			rings[i][j] = glm::rotateY(rings[i][j], (float)(i*360.f / halfRingCount));
		}
	}

	//connect points

	for (int i = 0; i < halfRingCount; i += 1)
	{
		AddTri( rings[i][0], antiPeak, rings[(i + 1) % halfRingCount][0]);
		for (int j = 0; j < partitions-2; j += 1)
		{
			AddQuad(rings[i][j],rings[(i + 1) % halfRingCount][j], rings[i][(j + 1)], rings[(i + 1) % halfRingCount][(j + 1)]);
		}
		AddTri(peak, rings[i][partitions - 2], rings[(i + 1) % halfRingCount][partitions - 2]);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}