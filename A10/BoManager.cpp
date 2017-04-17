#pragma once
#include "BoManager.h"

BoManager* BoManager::instance = nullptr;

void BoManager::addBo(std::vector<vector3> verts, String name)
{
	m_boMap.insert(std::pair<String, MyBoundingObjectClass*>(name, new MyBoundingObjectClass(verts)));
}
void BoManager::checkColls()
{
	for (std::map<String, MyBoundingObjectClass*>::iterator bo0 = m_boMap.begin(); bo0 != m_boMap.end(); ++bo0)
	{
		bo0->second->SetColliding(false);
	}
	for (std::map<String, MyBoundingObjectClass*>::iterator bo0 = m_boMap.begin(); bo0 != m_boMap.end(); ++bo0)
	{
		for (std::map<String, MyBoundingObjectClass*>::iterator bo1 = bo0; bo1 != m_boMap.end(); ++bo1)
		{
			if (bo0->second->IsColliding(bo1->second))
			{
				bo0->second->SetColliding(true);
				bo1->second->SetColliding(true);
			}
		}
	}
}
void BoManager::updateModelMatrix(String name, matrix4 mat)
{
	if (m_boMap[name] == nullptr)
		return;
	m_boMap[name]->SetModelMatrix(mat);
} 
void BoManager::render()
{
	for (std::map<String, MyBoundingObjectClass*>::iterator bo0 = m_boMap.begin(); bo0 != m_boMap.end(); ++bo0)
	{
		bo0->second->Render();
	}
}

