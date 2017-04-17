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
	std::map<String, MyBoundingObjectClass*> m_boMap;
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
	void addBo(std::vector<vector3> verts, String name);
	void checkColls();
	void updateModelMatrix(String name, matrix4 mat);
	void render();
};
