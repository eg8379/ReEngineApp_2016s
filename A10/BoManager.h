#pragma once
#include "MyBoundingObjectClass.h"

class BoManager {
	static BoManager* instance;

private:
	BoManager() {};
	BoManager(BoManager const& other) {
		m_boMap.clear();
		m_boMap = other.m_boMap;
	};
	BoManager& operator=(BoManager const& other) {
		if (&other == this)
			return *this;
		m_boMap.clear();
		m_boMap = other.m_boMap;
		return *this;
	};

public:
	std::map<String, MyBoundingObjectClass> m_boMap;

	static BoManager* GetInstance() {
		if (instance == nullptr)
			instance = new BoManager();
		return instance;
	}
	static void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
	void addBo(std::vector<vector3> verts, String name)
	{
		m_boMap.insert(std::pair<String, MyBoundingObjectClass>(name, MyBoundingObjectClass(verts)));
	}
	void checkColls()
	{
		for (std::map<String, MyBoundingObjectClass>::iterator bo0 = m_boMap.begin(); bo0 != m_boMap.end(); ++bo0)
		{
			for (std::map<String, MyBoundingObjectClass>::iterator bo1 = bo0; bo1 != m_boMap.end(); ++bo1)
			{
				if (bo0->second.IsColliding(bo1->second))
				{
					bo0->second.SetColliding();
					bo1->second.SetColliding();
				}
			}
		}
	}
	void updateModelMatrix(String name, matrix4 mat)
	{
		m_boMap[name].SetModelMatrix(mat);
	}
};